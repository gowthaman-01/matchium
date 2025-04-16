#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

/**
 * @brief Creates and configures a TCP socket.
 *
 * This function creates a TCP socket using the IPv4 address family and stream-based communication.
 * It also sets the SO_REUSEADDR option to ensure that the socket can be reused after program restarts.
 *
 * @return The file descriptor representing the created TCP socket.
 * @throws If socket creation or configuration fails, the error-handling function is triggered.
 */
int create_tcp_socket();

/**
 * @brief Creates and returns a configured sockaddr_in structure for a server.
 *
 * This function sets up a sockaddr_in instance configured for the IPv4
 * address family (AF_INET), binding to all interfaces (INADDR_ANY),
 * and using the specified port number.
 *
 * @param port The port number to assign to the sockaddr_in structure.
 * @return A sockaddr_in instance configured with the given port,
 *         ready to be used for binding a socket.
 */
sockaddr_in create_server_address(int port);
