#if !defined(A2_RULECLASS_H)
#define A2_RULECLASS_H

#include <iostream>
#include <exception>
#include <cstring>
#include <memory>
#include <vector>

#include "parselib.h"
#include "HeaderClass.h"

#define RULE_DELIM std::string (" ")
#define HEADER_DELIM std::string(" ")

#define RULE_PRINT_IP_RANGES "src= %s, dest= %s, "
#define RULE_PRINT_FORWARD_TYPE "action= FORWARD:%d, "
#define RULE_PRINT_DROP_TYPE "action= DROP, "
#define RULE_PRINT_PRIORITY_PKT_COUNT "pri= %d, pktCount= %d"

#define ERR_RULE_DESERIALIZE_FUNC std::string("Rule::deserialize()")

#define ERR_RULE_SER_FORMAT "Invalid serialized Rule string\n"

enum ActType {AT_FORWARD, AT_DROP};

class Rule_Exception : public Traceback_Exception {
	public:
		Rule_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) 
		: Traceback_Exception(msg, cur_func, func_traceback) {}
		Rule_Exception(const char* msg, const std::string cur_func)
		: Traceback_Exception(msg, cur_func) {}
};

class Rule {
	public:
		IP_Range src_ip, dest_ip;
		int pri, pkt_count;
		ActType act_type;
		SwPort act_val;

		Rule(std::string& serial_rule);
		Rule(IP_Range src_ip, IP_Range dest_ip, ActType act_type, SwPort act_val, int pri) 
			: src_ip(src_ip),
			  dest_ip(dest_ip),
			  pri(pri),
			  act_type(act_type),
			  act_val(act_val) {}

		void serialize(std::string& ser_rule);
		void deserialize(std::string& ser_rule);
		bool is_match(Header& header);
		void print();
		void add_pkt();
};

#endif
