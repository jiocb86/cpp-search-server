#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server) :
    ss_(search_server),
    no_result_request_(0),
    time_(0) {
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {
    const auto result = ss_.FindTopDocuments(raw_query, status);
    AddRequest(result.size());
    return result;
}
    
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    const auto result = ss_.FindTopDocuments(raw_query);
    AddRequest(result.size());
    return result;
}
    
int RequestQueue::GetNoResultRequests() const {
    return no_result_request_;
}

void RequestQueue::AddRequest(int results_num) {
    ++time_;
    requests_.push_back({time_, results_num});
    while (min_in_day_ == requests_.size() - 1) {
        if (requests_.front().count_results == 0) {
            --no_result_request_;
        }
        requests_.pop_front();
    } 
    if (results_num == 0) {
        ++no_result_request_;
    } 
}
