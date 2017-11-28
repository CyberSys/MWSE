/************************************************************************
	
	xFileReadShort.cpp - Copyright (c) 2008 The MWSE Project
	http://www.sourceforge.net/projects/mwse

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

**************************************************************************/

#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "FileUtil.h"

#include <list>

using namespace mwse;

namespace mwse
{
	class xFileReadShort : mwse::InstructionInterface_t
	{
	public:
		xFileReadShort();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xFileReadShortOpcode = 0x3C11;
	static xFileReadShort xFileReadShortInstance;

	xFileReadShort::xFileReadShort() : mwse::InstructionInterface_t(xFileReadShortOpcode) {}

	void xFileReadShort::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xFileReadShort::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		if (mwse::Stack::getInstance().size() < 2) {
			mwse::log::getLog() << "xFileReadShort: Function called with too few arguments." << std::endl;
			return 0.0f;
		}

		// Get arguments from the stack.
		mwseString_t fileName = virtualMachine.getString(mwse::Stack::getInstance().popLong());
		mwLong_t count = mwse::Stack::getInstance().popLong();

		// Gather values into a temporary list, so they aren't in reverse order.
		std::list<mwShort_t> values;
		for (mwLong_t i = 0; i < count; i++) {
			mwShort_t value = mwse::FileSystem::getInstance().readShort(fileName.c_str());
			values.push_front(value);
		}

		// Copy values from the temporary vector to the stack.
		mwLong_t size = values.size();
		while (!values.empty()) {
			mwse::Stack::getInstance().pushShort(values.front());
			values.pop_front();
		}
		mwse::Stack::getInstance().pushLong(size);

		return 0.0f;
	}
}