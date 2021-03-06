// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef PLASMA_IO_H
#define PLASMA_IO_H

#include <inttypes.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "arrow/status.h"

// TODO(pcm): Replace our own custom message header (message type,
// message length, plasma protocol verion) with one that is serialized
// using flatbuffers.
#define PLASMA_PROTOCOL_VERSION 0x0000000000000000
#define DISCONNECT_CLIENT 0

arrow::Status WriteBytes(int fd, uint8_t* cursor, size_t length);

arrow::Status WriteMessage(int fd, int64_t type, int64_t length, uint8_t* bytes);

arrow::Status ReadBytes(int fd, uint8_t* cursor, size_t length);

arrow::Status ReadMessage(int fd, int64_t* type, std::vector<uint8_t>* buffer);

int bind_ipc_sock(const std::string& pathname, bool shall_listen);

int connect_ipc_sock(const std::string& pathname);

int connect_ipc_sock_retry(const std::string& pathname, int num_retries, int64_t timeout);

int AcceptClient(int socket_fd);

uint8_t* read_message_async(int sock);

#endif  // PLASMA_IO_H
