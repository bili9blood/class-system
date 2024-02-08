#pragma once

#include <hv/Buffer.h>

namespace logic {

/**
 * @brief Handle the request from client and return a response
 *
 * @param req the request from client
 * @return hv::BufferPtr response buffer
 */
hv::BufferPtr HandleRequest(hv::Buffer* req);

}
