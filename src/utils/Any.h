//This container was provided by Karlheinz Wohlmuth <khwhth@gmail.com>.
#ifndef ANY_H_
#define ANY_H_

#include <memory>
#include <utility>
#include <typeinfo>
#include <type_traits>
#include <stdexcept>

namespace yagi {
namespace container {
class Any
{
private:
    template<typename Base, typename T>
    using remove_if_derived_or_equal = typename std::enable_if<!std::is_base_of<Base, typename std::remove_reference<T>::type>::value>::type;

    struct HolderBase
    {
        virtual ~HolderBase() { }
        virtual const std::type_info& getType() const noexcept = 0;
    };

    template<typename T>
    struct Holder final : HolderBase
    {
        template<typename H, typename = remove_if_derived_or_equal<Holder, H>>
        explicit Holder(H &&h): t_{std::forward<H>(h)} { }

        const std::type_info& getType() const noexcept override { return typeid(t_); }
        T t_;
    };

public:
    Any() = default;
    Any(const Any &) = default;
    Any(Any &&other) noexcept: haveValue_{std::move(other.haveValue_)}, holder_{std::move(other.holder_)} { other.haveValue_ = false; }
    template<typename T, typename = remove_if_derived_or_equal<Any, T>>
    explicit Any(T &&t): haveValue_{true}, holder_{std::make_shared<Holder<typename std::remove_reference<T>::type>>(std::forward<T>(t))} { }
    virtual ~Any() = default;

    explicit operator bool() const noexcept { return !empty(); }
    Any& operator=(const Any &) = default;
    Any& operator=(Any &&other) noexcept { haveValue_ = std::move(other.haveValue_); holder_ = std::move(other.holder_); other.haveValue_ = false; return *this; }

    friend bool operator==(const Any &a, const Any &b) noexcept { return a.haveValue_ == b.haveValue_ && a.holder_ == b.holder_; }
    friend bool operator!=(const Any &a, const Any &b) noexcept { return a.haveValue_ != b.haveValue_ || a.holder_ != b.holder_; }

    template<typename T>
    Any clone() const { return empty() ? Any{} : Any{T{get<T>()}}; }
    template<typename T>
    bool hasType() const noexcept { return haveValue_ ? holder_->getType() == typeid(T) : false; }
    template<typename T>
    T& get() { check<T>(); return static_cast<Holder<T>*>(holder_.get())->t_; }
    template<typename T>
    const T& get() const { check<T>(); return static_cast<Holder<T>*>(holder_.get())->t_; }
    template<typename T>
    T tryGetCopy(T t = T{}) const { if (empty()) return std::move(t); return get<T>(); }
    template<typename T>
    void set(T &&t) { holder_.reset(); holder_ = std::make_shared<Holder<typename std::remove_reference<T>::type>>(std::forward<T>(t)); }
    bool empty() const noexcept { return !haveValue_; }
    void reset() noexcept { haveValue_= false; holder_.reset(); }

private:
    bool haveValue_ = false;
    std::shared_ptr<HolderBase> holder_;

    template<typename T>
    void check() const { if (empty()) throw std::runtime_error("[any] no value set"); if (!hasType<T>()) throw std::runtime_error("[any] invalid type"); }
};
} //end namespace
}
#endif //ANY_H_
