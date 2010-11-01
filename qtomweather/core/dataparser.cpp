#include "dataparser.h"
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
namespace Core {
////////////////////////////////////////////////////////////////////////////////
    DataParser::DataParser(const std::string& filename) : Parser() {
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
        try{
#endif //LIBXMLCPP_EXCEPTIONS_ENABLED
            validator->parse_file(filename);
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
        }
        catch(const std::exception& ex){
            std::cout << "Exception caught: " << ex.what() << std::endl;
        }
#endif //LIBXMLCPP_EXCEPTIONS_ENABLED

    }
////////////////////////////////////////////////////////////////////////////////
    DataParser::DataParser() : Parser() {
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
        try{
#endif //LIBXMLCPP_EXCEPTIONS_ENABLED

        validator->parse_file("/usr/share/omweather/schemas/data.xsd");
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
        }
        catch(const std::exception& ex){
            std::cout << "Exception caught: " << ex.what() << std::endl;
        }
#endif //LIBXMLCPP_EXCEPTIONS_ENABLED

    }
////////////////////////////////////////////////////////////////////////////////
    DataParser::~DataParser(){
    }
////////////////////////////////////////////////////////////////////////////////
    bool
    DataParser::parse(const std::string& filename){
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
        try{
#endif //LIBXMLCPP_EXCEPTIONS_ENABLED
            if(validator->validate(filename))
                std::cout << "Document is not valid." << std::endl;
            parser->parse_file(filename);
            if(parser){
                //Walk the tree:
                const xmlpp::Node* pNode = parser->get_document()->get_root_node(); //deleted by DomParser.
                processNode(pNode);
            }
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
        }
        catch(const std::exception& ex){
            std::cout << "Exception caught: " << ex.what() << std::endl;
            return FALSE;
        }
#endif //LIBXMLCPP_EXCEPTIONS_ENABLED
        return TRUE;
    }
////////////////////////////////////////////////////////////////////////////////
    void DataParser::processNode(const xmlpp::Node* node){
        if(!node)
            return;
        std::cout << "Node name: " << node->get_name() << std::endl;
        if(const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(node)){

        }
    }
////////////////////////////////////////////////////////////////////////////////
} // namespace Core