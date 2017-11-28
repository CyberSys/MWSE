/************************************************************************
	
	xSetArrayValue.cpp - Copyright (c) 2008 The MWSE Project
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
#include "ArrayUtil.h"

using namespace mwse;

namespace mwse
{
	class xSetArrayValue : mwse::InstructionInterface_t
	{
	public:
		xSetArrayValue();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xSetArrayValueOpcode = 0x3933;
	static xSetArrayValue xSetArrayValueInstance;

	xSetArrayValue::xSetArrayValue() : mwse::InstructionInterface_t(xSetArrayValueOpcode) {}

	void xSetArrayValue::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xSetArrayValue::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		if (mwse::Stack::getInstance().size() < 3) {
			mwse::log::getLog() << "xSetArrayValue: Function called with too few arguments." << std::endl;
			mwse::Stack::getInstance().pushLong(0);
			return 0.0f;
		}

		mwLong_t id = mwse::Stack::getInstance().popLong();
		mwLong_t index = mwse::Stack::getInstance().popLong();
		mwLong_t value = mwse::Stack::getInstance().popLong();

		mwLong_t status = mwse::Arrays::getInstance().setValue("xSetArrayValue", id, index, value);

		mwse::Stack::getInstance().pushLong(status);

		return 0.0f;
	}
}