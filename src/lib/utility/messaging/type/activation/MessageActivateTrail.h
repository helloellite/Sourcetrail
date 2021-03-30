#ifndef MESSAGE_ACTIVATE_TRAIL_H
#define MESSAGE_ACTIVATE_TRAIL_H

#include "Message.h"
#include "MessageActivateBase.h"
#include "NodeType.h"
#include "TabId.h"
#include "types.h"

class MessageActivateTrail
	: public Message<MessageActivateTrail>
	, public MessageActivateBase
{
public:
	MessageActivateTrail(
		Id originId, Id targetId, Edge::TypeMask edgeTypes, size_t depth, bool horizontalLayout)
		: originId(originId)
		, targetId(targetId)
		, nodeTypes(0)
		, edgeTypes(edgeTypes)
		, nodeNonIndexed(false)
		, depth(depth)
		, horizontalLayout(horizontalLayout)
		, custom(false)
		, trailSbling(false)
		, expandMembers(false)
		, breakMemberBox(true)
	{
		setSchedulerId(TabId::currentTab());
	}

	MessageActivateTrail(
		Id originId,
		Id targetId,
		NodeKindMask nodeTypes,
		Edge::TypeMask edgeTypes,
		bool nodeNonIndexed,
		size_t depth,
		bool horizontalLayout,
		bool trailSbling=false,
		bool expandMembers=false,
		bool breakMemberBox=true)
		: originId(originId)
		, targetId(targetId)
		, nodeTypes(nodeTypes)
		, edgeTypes(edgeTypes)
		, nodeNonIndexed(nodeNonIndexed)
		, depth(depth)
		, horizontalLayout(horizontalLayout)
		, custom(true)
		, trailSbling(trailSbling)
		, expandMembers(expandMembers)
		, breakMemberBox(breakMemberBox)
	{
		setSchedulerId(TabId::currentTab());
	}

	static const std::string getStaticType()
	{
		return "MessageActivateTrail";
	}

	std::vector<SearchMatch> getSearchMatches() const override
	{
		return searchMatches;
	}

	std::vector<SearchMatch> searchMatches;

	const Id originId;
	const Id targetId;
	const NodeKindMask nodeTypes;
	const Edge::TypeMask edgeTypes;
	const bool nodeNonIndexed;
	const size_t depth;
	const bool horizontalLayout;
	const bool custom;
	const bool trailSbling;
	const bool expandMembers;
	const bool breakMemberBox;
};

#endif	  // MESSAGE_ACTIVATE_TRAIL_H
