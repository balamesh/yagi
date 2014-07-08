//This container was provided by Karlheinz Wohlmuth <khwhth@gmail.com>.
#ifndef ANY_H_
#define ANY_H_

#include <memory>
#include <utility>
#include <typeinfo>
#include <type_traits>
#include <stdexcept>

namespace container {
class Any final
{
private:
    struct HolderBase
    {
        virtual ~HolderBase() { }
        virtual const std::type_info& getType() const noexcept(true) = 0;
    };

    template<typename T>
    struct Holder : HolderBase
    {
        explicit Holder(T t): t_{std::move(t)} { }
        const std::type_info& getType() const noexcept(true) override { return typeid(t_); }
        T t_;
    };

public:
    Any(): holder_{nullptr} { }
    template<typename T, typename = typename std::enable_if<!std::is_same<typename std::remove_reference<T>::type, Any>::value>::type> explicit Any(T &&t): haveValue_{true}, holder_{std::make_shared<Holder<typename std::remove_reference<T>::type>>(std::forward<T>(t))} { }
    Any(const Any &other): haveValue_{other.haveValue_}, holder_{other.holder_} { }
    Any(Any &&other): haveValue_{std::move(other.haveValue_)}, holder_{std::move(other.holder_)} { other.haveValue_ = false; }
    ~Any() { }
    Any& operator=(const Any &other) { haveValue_ = other.haveValue_; holder_ = other.holder_; return *this; }
    Any& operator=(Any &&other) { haveValue_ = std::move(other.haveValue_); holder_ = std::move(other.holder_); other.haveValue_ = false; return *this; }

    template<typename T> Any clone() const { check<T>(); return Any{T{get<T>()}}; }
    template<typename T> bool hasType() const noexcept(true) { return haveValue_ ? holder_->getType() == typeid(T) : false; }
    void reset() noexcept(true) { haveValue_= false; holder_.reset(); }
    bool empty() const noexcept(true) { return !haveValue_; }
    template<typename T> T& get() { check<T>(); return static_cast<Holder<T>*>(holder_.get())->t_; }
    template<typename T> const T& get() const { check<T>(); return static_cast<Holder<T>*>(holder_.get())->t_; }
    template<typename T> void set(T &&t) { holder_.reset(); holder_ = std::make_shared<Holder<typename std::remove_reference<T>::type>>(std::forward<T>(t)); }

private:
    bool haveValue_ = false;
    std::shared_ptr<HolderBase> holder_;

    template<typename T> void check() const { if (empty()) throw std::runtime_error("no value set"); if (!hasType<T>()) throw std::runtime_error("invalid type"); }
};
}
#endif //ANY_H_
