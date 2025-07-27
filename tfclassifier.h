#pragma once

#include <string>
#include <vector>
#include <memory>

#include <tensorflow/c/c_api.h>

class TfClassifier
{
public:
    using features_t = std::vector<float>;
    using probas_t = std::vector<float>;

    TfClassifier(const std::string& modelPath,
                 const int width,
                 const int height);

    TfClassifier(const TfClassifier&) = delete;
    
    TfClassifier& operator=(const TfClassifier&) = delete;
    
    size_t num_classes() const;
    
    size_t predict(const features_t&) const;

    probas_t predict_proba(const features_t&) const;

private:
    static void delete_tf_session(TF_Session*);

    using tf_graph = std::unique_ptr<TF_Graph, decltype(&TF_DeleteGraph)>;
    using tf_buffer = std::unique_ptr<TF_Buffer, decltype(&TF_DeleteBuffer)>;
    using tf_import_graph_def_options = std::unique_ptr<TF_ImportGraphDefOptions, decltype(&TF_DeleteImportGraphDefOptions)>;
    using tf_status = std::unique_ptr<TF_Status, decltype(&TF_DeleteStatus)>;
    using tf_session_options = std::unique_ptr<TF_SessionOptions, decltype(&TF_DeleteSessionOptions)>;
    using tf_tensor = std::unique_ptr<TF_Tensor, decltype(&TF_DeleteTensor)>;
    using tf_session = std::unique_ptr<TF_Session, decltype(&delete_tf_session)>;

    tf_graph m_graph{TF_NewGraph(), TF_DeleteGraph};
    tf_session_options m_session_opts{TF_NewSessionOptions(), TF_DeleteSessionOptions};
    tf_session m_session = {nullptr, delete_tf_session};
    TF_Operation* m_input_op = nullptr;
    TF_Operation* m_output_op = nullptr;
    int m_width;
    int m_height;
};