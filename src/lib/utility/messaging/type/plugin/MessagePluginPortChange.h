#ifndef MESSAGE_PLUGIN_PORT_CHANGE_H
#define MESSAGE_PLUGIN_PORT_CHANGE_H

#include "Message.h"

class MessagePluginPortChange: public Message<MessagePluginPortChange>
{
public:
	int pluginPort;
	int sourcetrailPort;
	MessagePluginPortChange(int pp=0, int sp=0):pluginPort(pp), sourcetrailPort(sp) {}

	static const std::string getStaticType()
	{
		return "MessagePluginPortChange";
	}
};

#endif	  // MESSAGE_PLUGIN_PORT_CHANGE_H
