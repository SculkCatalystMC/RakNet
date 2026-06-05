/*
 *  Copyright (c) 2025, SculkCatalystMC.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */


#include "EmptyHeader.h"

#ifndef _WIN32
#include <netdb.h>
#endif

#ifdef RAKNET_SOCKET_2_INLINE_FUNCTIONS

#ifndef RAKNETSOCKET2_BERKLEY_NATIVE_CLIENT_CPP
#define RAKNETSOCKET2_BERKLEY_NATIVE_CLIENT_CPP

// Every platform except windows store 8 and native client supports Berkley sockets
#if !defined(WINDOWS_STORE_RT)

#include "Itoa.h"

// Shared on most platforms, but excluded from the listed


void DomainNameToIP_Berkley_IPV4And6(const char* domainName, char ip[65]) {
#if RAKNET_SUPPORT_IPV6 == 1
    // Ensure the output buffer is always initialized.
    const size_t IP_BUFFER_SIZE = 65;
    memset(ip, 0, IP_BUFFER_SIZE);

    if (domainName == nullptr || domainName[0] == '\0') {
        return;
    }

    struct addrinfo hints, *res = nullptr, *p = nullptr;
    int             status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC; // Support both IPv4 and IPv6.
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags    = AI_ADDRCONFIG; // Return address families available on this host.

    status = getaddrinfo(domainName, NULL, &hints, &res);
    if (status != 0 || res == nullptr) {
        return;
    }

    // Iterate all returned addresses.
    for (p = res; p != nullptr; p = p->ai_next) {
        if (p->ai_family == AF_INET) {
            // IPv4 handling.
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
            inet_ntop(AF_INET, &(ipv4->sin_addr), ip, IP_BUFFER_SIZE);
            break; // Use the first IPv4 address.
        }
#if RAKNET_SUPPORT_IPV6 == 1
        else if (p->ai_family == AF_INET6) {
            // IPv6 handling.
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
            inet_ntop(AF_INET6, &(ipv6->sin6_addr), ip, IP_BUFFER_SIZE);
            break; // Use the first IPv6 address.
        }
#endif
    }

    freeaddrinfo(res);
#else
    // Fallback when IPv6 is not enabled.
    (void)domainName;
    memset(ip, 0, 65);
#endif
}


void DomainNameToIP_Berkley_IPV4(const char* domainName, char ip[65]) {
    static struct in_addr addr;
    memset(&addr, 0, sizeof(in_addr));

    // Use inet_addr instead? What is the difference?
    struct hostent* phe = gethostbyname(domainName);

    if (phe == 0 || phe->h_addr_list[0] == 0) {
        // cerr << "Yow! Bad host lookup." << endl;
        memset(ip, 0, 65 * sizeof(char));
        return;
    }

    if (phe->h_addr_list[0] == 0) {
        memset(ip, 0, 65 * sizeof(char));
        return;
    }

    memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
    strcpy(ip, inet_ntoa(addr));
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
