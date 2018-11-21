#if !defined(A2_PKTCLASS_H)
#define A2_PKTCLASS_H

#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <cstring>
#include <memory>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parselib.h"

#define PKT_LEN 127
#define PKT_DELIM std::string (" ")
#define PKT_EMPTY_MSG std::string("")

#define PTYPE_STR_OPEN "[OPEN]"
#define PTYPE_STR_ACK "[ACK]"
#define PTYPE_STR_QUERY "[QUERY]"
#define PTYPE_STR_ADD "[ADD]"
#define PTYPE_STR_RELAY "[RELAY]"

#define ERR_PKT_READ_FD_FUNC std::string("Packet::read_from_fd()")
#define ERR_PKT_WRITE_FD_FUNC std::string("Packet::write_to_fd()")
#define ERR_PKT_PRINT_LOG_FUNC std::string("Packet::print_log()")
#define ERR_PKT_DESERIALIZE_FUNC std::string("Packet::print_log()")

#define ERR_PKT_READ "Error during read from file descriptor\n"
#define ERR_PKT_WRITE "Error during write to file descriptor\n"
#define ERR_PKT_SER_FORMAT "Invalid format given in serialized Packet"

typedef enum {PT_UNINIT, PT_OPEN, PT_ACK, PT_QUERY, PT_ADD, PT_RELAY, PT_ADMIT} PktType;


class Pkt_Exception : public Traceback_Exception {
	public:
		Pkt_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) 
		: Traceback_Exception(msg, cur_func, func_traceback) {}
		Pkt_Exception(const char* msg, const std::string cur_func)
		: Traceback_Exception(msg, cur_func) {}
};

class Packet {
	public:
		PktType ptype;
		std::string msg;
	
		Packet();
		Packet(PktType ptype);
		Packet(PktType ptype, std::string& msg);
		Packet(std::string& pkt);

		void set_msg(std::string& new_msg);
		void serialize(std::string& ser_pkt);
		void deserialize(std::string& ser_pkt);
		size_t read_from_fd(int fd);
		size_t write_to_fd(int fd);
};

#endif