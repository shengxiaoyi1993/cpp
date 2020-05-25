#ifndef BS_CXX_DRIVER_H
#define BS_CXX_DRIVER_H
//#include <mongoc/mongoc.h>
#include <stdio.h>
//#include <bson/bson.h>
#include "../../lib/hex/hex.h"
#include <iostream>

#include "bsoncxx/json.hpp"
#include <bsoncxx/document/view.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>


#include "bs_cxx_driver_global.h"



namespace mongo {
 void Init();
 void Cleanup();
}


#endif // BS_CXX_DRIVER_H
