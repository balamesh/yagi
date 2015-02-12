#ifndef IFILEEXOGENOUSEVENTPRODUCER_H_
#define IFILEEXOGENOUSEVENTPRODUCER_H_

#include "../../ExogenousEvents/IExogenousEventProducer.h"
#include <chrono>

namespace yagi {
namespace execution {

class FileExogenousEventProducer : public IExogenousEventProducer
{
        const std::string fileName = "exoEventData.txt";

        std::vector<std::tuple<std::string, std::string, std::string>> splitFileLines(
            std::vector<std::string> lines);

        std::vector<std::string> readLinesFromFile();

        bool file_exists_;
        std::chrono::time_point<std::chrono::system_clock> time_point_file_found_;
public:
        FileExogenousEventProducer();
    bool eventAvailable() override;
    std::vector<std::pair<std::string, std::unordered_map<std::string, std::string> > > getEvent() override;
};

} /* namespace execution */
} /* namespace yagi */

#endif /* IDEFAULTEXOGENOUSEVENTPRODUCER_H_ */
