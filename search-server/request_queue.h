#pragma once
#include <deque>
#include <vector>
#include <string>
#include "search_server.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);    
    int GetNoResultRequests() const;
private:
    struct QueryResult {
        uint64_t time_document;
        int count_results;
    };
    std::deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    const SearchServer &ss_;
    int no_result_request_;
    uint64_t time_;
    
    void AddRequest(int results_num);
};

template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
    const auto result = ss_.FindTopDocuments(raw_query, document_predicate);
    AddRequest(result.size());
    return result;
}
