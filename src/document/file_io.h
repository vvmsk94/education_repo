#ifndef FILE_IO_H
#define FILE_IO_H

#include "document.h"

#include <string>

namespace my
{

namespace file_io
{

inline Document::Ptr import_document(const std::string& /*filename*/)
{
    return std::make_unique<Document>();
}

inline void export_document(const Document::Ptr& /*document*/, const std::string& /*filename*/)
{
}

} // namespace file_op

} // namespace my

#endif // FILE_IO_H
