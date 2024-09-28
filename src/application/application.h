#ifndef APPLICATION_H
#define APPLICATION_H

#include "../document/document.h"
#include "../document/file_io.h"

#include <string>
#include <unordered_set>
#include <cassert>

namespace my
{

class Application
{
public:
    const Document::Ptr& create_document()
    {
        auto [it, b_inserted] = m_documents.emplace(std::make_unique<Document>());
        assert(b_inserted);
        return *it;
    }

    const Document::Ptr& import_document(const std::string& filename)
    {
        auto [it, b_inserted] = m_documents.emplace(file_io::import_document(filename));
        assert(b_inserted);
        return *it;
    }

    void export_document(const Document::Ptr& document, const std::string& filename)
    {
        file_io::export_document(document, filename);
    }

    bool close_document(const Document::Ptr& document)
    {
        std::size_t removed = m_documents.erase(document);
        if (removed == 0)
            return false;
        return true;
    }

private:
    std::unordered_set<Document::Ptr> m_documents;
};

} // namespace my

#endif // APPLICATION_H
