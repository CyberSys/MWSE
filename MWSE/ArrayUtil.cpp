#include "ArrayUtil.h"

namespace mwse {
	Arrays Arrays::singleton;

	Arrays::Arrays() {
		arrays = Arrays_t();
	}

	size_t Arrays::create(std::string const& caller) {
		size_t id = 0;
		if (arrays.size() < maxArrayId) {
			id = arrays.size() + 1;
			arrays.push_back(std::vector<ArrayItem_t>());
		}
		else {
			mwse::log::getLog() << caller << ": Unable to create array. Maximum number of arrays reached. id: " << id << std::endl;
		}
		return id;
	}

	ArrayItem_t Arrays::getValue(std::string const& caller, size_t const id, size_t const index) {
		ArrayItem_t value = 0;
		if (id > 0 && id <= arrays.size()) {
			std::vector<ArrayItem_t> const& a = arrays[id - 1];
			if (index >= 0 && index < a.size()) {
				value = a[index];
			}
			else {
				mwse::log::getLog() << caller << ": Array index out of bounds. id: " << id << " index: " << index << std::endl;
			}
		}
		else {
			mwse::log::getLog() << caller << ": Invalid array id: " << id << std::endl;
		}
		return value;
	}

	mwLong_t Arrays::setValue(std::string const& caller, size_t const id, size_t const index, ArrayItem_t const value) {
		mwLong_t success = 0;
		if (id > 0 && id <= arrays.size()) {
			if (index >= 0) {
				std::vector<ArrayItem_t>& a = arrays[id - 1];
				if (index + 1 > a.size()) {
					a.resize(index + 1);
				}
				a[index] = value;
				success = 1;
			}
			else {
				mwse::log::getLog() << caller << ": Array index out of bounds. id: " << id << " index: " << index << std::endl;
			}
		}
		else {
			mwse::log::getLog() << caller << ": Invalid array id: " << id << std::endl;
		}
		return success;
	}

	size_t Arrays::getSize(std::string const& caller, size_t const id)
	{
		size_t size = 0;
		if (id > 0 && id <= arrays.size()) {
			size = arrays[id - 1].size();
		}
		else {
			mwse::log::getLog() << caller << ": Invalid array id: " << id << std::endl;
		}
		return size;
	}

	mwLong_t Arrays::clear(std::string const& caller, size_t const id)
	{
		mwLong_t success = 0;
		if (id > 0 && id <= arrays.size()) {
			arrays[id - 1].clear();
			success = 1;
		}
		else {
			mwse::log::getLog() << caller << ": Invalid array id: " << id << std::endl;
		}
		return success;
	}

	Arrays_t& Arrays::get() {
		return arrays;
	}
}