/**
 * CMPUT 379 - Assignment 3
 * File Name: RuleClass.cc
 * Student Name: Jacob Bakker
 *
 * Implements class for pattern-action Rules to be stored in a Switch's flow table.
 *
 * Rules can be created either by supplying all required attributes (e.g. source/destination
 * IP ranges, action type) or with a serialized Rule string.
 * Implements methods for matching Header objects to Rules, incrementing packet counts, and
 * printing a formatted message containing the Rule's attributes.
 */

#include "RuleClass.h"

/**
 * Rule constructors
 */
Rule::Rule(std::string& ser_rule) {
	this->deserialize(ser_rule);
}

Rule::Rule(IP_Range src_ip, IP_Range dest_ip, ActType act_type, SwPort act_val, int pri) {
	this->src_ip = src_ip;
	this->dest_ip = dest_ip;
	this->act_type = act_type;
	this->act_val = act_val;
	this->pri = pri;
	this->pkt_count = 0;
}

/**
 * Function: deserialize
 * -----------------------
 * Sets Rule attributes to those specified in serialized Rule string.
 *
 * Parameters:
 * 	- ser_rule: Serialized Rule object
 * Return Value: None
 * Throws:
 *	- Rule_Exception
 */
void Rule::deserialize(std::string& ser_rule) {
	std::vector<std::string> toks, &toks_ptr = toks;
	int count;

	count = tok_split(ser_rule, RULE_DELIM, toks_ptr);
	if (count != 8) { throw Rule_Exception(ERR_RULE_SER_FORMAT, ERR_RULE_DESERIALIZE_FUNC, 0); }

	try {
	this->src_ip.low = str_to_int(toks.at(0));
	this->src_ip.high = str_to_int(toks.at(1));

	this->dest_ip.low = str_to_int(toks.at(2));
	this->dest_ip.high = str_to_int(toks.at(3));

	this->act_type = static_cast<ActType>(str_to_int(toks.at(4)));
	this->act_val = static_cast<SwPort>(str_to_int(toks.at(5)));
	this->pri = str_to_int(toks.at(6));
	this->pkt_count = str_to_int(toks.at(7));
	} catch (Parse_Exception& e) { throw Rule_Exception(e.what(), ERR_RULE_DESERIALIZE_FUNC, e.get_traceback(), e.get_error_code()); }
}

/**
 * Function: serialize
 * -----------------------
 * Serializes Rule object and assigns result to "ser_rule".
 *
 * Parameters:
 * 	- ser_rule: Stores serialized Rule object
 * Return Value: None
 * Throws: None
 */
void Rule::serialize(std::string& ser_rule) {
	ser_rule.clear();
	ser_rule += std::to_string(this->src_ip.low) + RULE_DELIM;
	ser_rule += std::to_string(this->src_ip.high) + RULE_DELIM;

	ser_rule += std::to_string(this->dest_ip.low) + RULE_DELIM;
	ser_rule += std::to_string(this->dest_ip.high) + RULE_DELIM;

	ser_rule += std::to_string(this->act_type) + RULE_DELIM;
	ser_rule += std::to_string(this->act_val) + RULE_DELIM;
	ser_rule += std::to_string(this->pri) + RULE_DELIM;
	ser_rule += std::to_string(this->pkt_count);
}

/**
 * Function: is_match
 * -----------------------
 * Returns true if Header source and destination IP values are in the IP ranges
 * given by the Rule object.
 *
 * Parameters:
 * 	- header: Header object.
 * Return Value:
 * 	- True if Header IP values are in range, false otherwise.
 * Throws: None
 */
bool Rule::is_match(Header& header) {
	if (this->src_ip.is_in_range(header.src_ip) == false) {
		return false;
	}
	if (this->dest_ip.is_in_range(header.dest_ip) == false) {
		return false;
	}
	return true;
}

/**
 * Function: add_pkt
 * -----------------------
 * Increments packet counter.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Rule::add_pkt() {
	this->pkt_count++;
}

/**
 * Function: print
 * -----------------------
 * Prints Rule attributes to stdout.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Rule::print() {
	std::string src_ip_str(""), dest_ip_str("");
	std::string action_str;

	std::cout << "(";
	// Print source and destination IP ranges
	this->src_ip.serialize(src_ip_str);
	this->dest_ip.serialize(dest_ip_str);
	fprintf(stdout, RULE_PRINT_IP_RANGES, src_ip_str.c_str(), dest_ip_str.c_str());
	// Print action type with port number for FORWARD types
	if (this->act_type == AT_FORWARD) {
		fprintf(stdout, RULE_PRINT_FORWARD_TYPE, this->act_val);
	} else {
		std::cout << RULE_PRINT_DROP_TYPE;
	}
	// Print priority and packet count
	fprintf(stdout, RULE_PRINT_PRIORITY_PKT_COUNT, this->pri, this->pkt_count);
	std::cout << ")\n";
}
