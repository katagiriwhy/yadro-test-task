#include "event_handler.hpp"
#include <string>

std::string ErrorToString(novokhatskiy::ErrorType e) {
    using namespace novokhatskiy;
    switch (e) {
        case ErrorType::NotOpenYet: return "NotOpenYet";
        case ErrorType::YouShallNotPass: return "YouShallNotPass";
        case ErrorType::ClientUnknown: return "ClientUnknown";
        case ErrorType::PlaceIsBusy: return "PlaceIsBusy";
        case ErrorType::ICanWaitNoLonger: return "ICanWaitNoLonger!";
    }

    return "";
}