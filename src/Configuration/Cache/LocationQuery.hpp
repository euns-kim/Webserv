#pragma once

#include <string>
#include <vector>

#include "Configuration/Directive.hpp"
#include "Configuration/Directive/Block.hpp"
#include "Configuration/Directive/Block/Location.hpp"
#include "Configuration/Directive/Block/Server.hpp"
#include "Configuration/Directive/Simple.hpp"
#include "Configuration/Directive/Simple/ErrorPage.hpp"
#include "Configuration/Directive/Simple/MimeTypes.hpp"
#include "Configuration/Directive/Simple/AllowMethods.hpp"
#include "Configuration/Directive/Simple/Return.hpp"
#include "Configuration/Directive/Simple/Cgi.hpp"

namespace cache
{

  typedef bool  (*DuplicateChecker)(std::vector<const Directive*>::iterator directive_it, const Directive* new_directive);

  bool  CheckCgi(std::vector<const Directive*>::iterator directive_it, const Directive* new_directive);
  bool  CheckIndex(std::vector<const Directive*>::iterator directive_it, const Directive* new_directive);
  bool  CheckErrorPage(std::vector<const Directive*>::iterator directive_it, const Directive* new_directive);

  /**
   * @brief Properties of a location block
  */
  struct LocationQuery
  {
    const directive::ServerBlock*             server_block;
    std::string                               match_path;
    // direvtives to decide if the request is allowed
    directive::Methods                        allowed_methods;
    size_t                                    client_max_body_size;
    // If return is not null, the request should be generated from this directive
    const directive::Return*                  redirect;
    // If cgi is not null, the request should be handled by a cgi script
    std::vector<const directive::Cgi*>        cgis;
    // directives to find the full path of the requested resource
    std::string                               root;
    std::vector<const directive::Index*>      indexes;
    bool                                      autoindex;
    const directive::MimeTypes*               mime_types;
    std::vector<const directive::ErrorPage*>  error_pages;
    std::string                               access_log;
    std::string                               error_log;

    LocationQuery();

    void  construct(const directive::ServerBlock*, const directive::LocationBlock* location_block);

    void  construct_match_path(const directive::LocationBlock* location_block);
    void  construct_allowed_methods(const directive::DirectiveBlock* target_block);
    void  construct_client_max_body_size(const directive::DirectiveBlock* target_block);
    void  construct_return(const directive::DirectiveBlock* target_block);
    void  construct_cgis(const directive::DirectiveBlock* target_block);
    void  construct_root(const directive::DirectiveBlock* target_block);
    void  construct_indexes(const directive::DirectiveBlock* target_block);
    void  construct_autoindex(const directive::DirectiveBlock* target_block);
    void  construct_mime_types(const directive::DirectiveBlock* target_block);
    void  construct_error_pages(const directive::DirectiveBlock* target_block);
    void  construct_access_log(const directive::DirectiveBlock* target_block);
    void  construct_error_log(const directive::DirectiveBlock* target_block);

    const Directive*                closest_directive(const directive::DirectiveBlock* location_block, Directive::Type type);
    std::vector<const Directive*>   collect_directives(const directive::DirectiveBlock* location_block, Directive::Type type, DuplicateChecker is_duplicated);
  };
} // namespace caches
