/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "EmptyHeader.h"

#ifdef RAKNET_SOCKET_2_INLINE_FUNCTIONS

#ifndef RAKNETSOCKET2_BERKLEY_NATIVE_CLIENT_CPP
#define RAKNETSOCKET2_BERKLEY_NATIVE_CLIENT_CPP

// Every platform except windows store 8 and native client supports Berkley
// sockets
#if !defined(WINDOWS_STORE_RT)

#if !defined(_WIN32)
#include <netdb.h>
#endif

#include "Itoa.h"

// Shared on most platforms, but excluded from the listed

void DomainNameToIP_Berkley_IPV4And6(const char* domainName, char ip[65]) {
#if RAKNET_SUPPORT_IPV6 == 1
    struct addrinfo hints, *res, *p;
    int             status;
    memset(&hints, 0, sizeof hints);
    hints.ai_family   = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_DGRAM;

    if ((status = getaddrinfo(domainName, NULL, &hints, &res)) != 0) {
        memset(ip, 0, 65);
        return;
    }

    p = res;
    // get the pointer to the address itself,
    // different fields in IPv4 and IPv6:
    if (p->ai_family == AF_INET) {
        struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
        if (inet_ntop(AF_INET, &(ipv4->sin_addr), ip, 65) == 0) {
            memset(ip, 0, 65 * sizeof(char));
        }
    } else {
        // TODO - test
        struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
        if (inet_ntop(AF_INET6, &(ipv6->sin6_addr), ip, 65) == 0) {
            memset(ip, 0, 65 * sizeof(char));
        }
    }
    freeaddrinfo(res); // free the linked list
#else
    (void)domainName;
    (void)ip;
#endif // #if RAKNET_SUPPORT_IPV6==1
}

void DomainNameToIP_Berkley_IPV4(const char* domainName, char ip[65]) {
    struct addrinfo hints, *res = 0;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    if (getaddrinfo(domainName, NULL, &hints, &res) != 0 || res == 0 || res->ai_addr == 0) {
        memset(ip, 0, 65 * sizeof(char));
        return;
    }

    const struct sockaddr_in* ipv4 = reinterpret_cast<const struct sockaddr_in*>(res->ai_addr);
    if (inet_ntop(AF_INET, &(ipv4->sin_addr), ip, 65) == 0) {
        memset(ip, 0, 65 * sizeof(char));
    }
    freeaddrinfo(res);
}

void DomainNameToIP_Berkley(const char* domainName, char ip[65]) {
#if RAKNET_SUPPORT_IPV6 == 1
    return DomainNameToIP_Berkley_IPV4And6(domainName, ip);
#else
    return DomainNameToIP_Berkley_IPV4(domainName, ip);
#endif
}

#endif // !defined(WINDOWS_STORE_RT) && !defined(__native_client__)

#endif // file header

#endif // #ifdef RAKNET_SOCKET_2_INLINE_FUNCTIONS
