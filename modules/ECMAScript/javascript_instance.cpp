/**************************************************************************/
/*  javascript_instance.cpp                                               */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "javascript_instance.h"
#include "javascript.h"
#include "javascript_language.h"

Ref<Script> JavaScriptInstance::get_script() const {
	return script;
}

void JavaScriptInstance::get_method_list(List<MethodInfo> *p_list) const {
	if (!javascript_class)
		return;
	for (const KeyValue<StringName, MethodInfo> &i : javascript_class->methods) {
		p_list->push_back(i.value);
	}
}

bool JavaScriptInstance::has_method(const StringName &p_method) const {
	if (!binder || !javascript_object.javascript_object)
		return false;
	return binder->has_method(javascript_object, p_method);
}

bool JavaScriptInstance::set(const StringName &p_name, const Variant &p_value) {
	if (!binder || !javascript_object.javascript_object)
		return false;
	return binder->set_instance_property(javascript_object, p_name, p_value);
}

bool JavaScriptInstance::get(const StringName &p_name, Variant &r_ret) const {
	if (!binder || !javascript_object.javascript_object)
		return false;
	return binder->get_instance_property(this->javascript_object, p_name, r_ret);
}

void JavaScriptInstance::get_property_list(List<PropertyInfo> *p_properties) const {
	if (!javascript_class)
		return;
	for (const KeyValue<StringName, JavaScriptProperyInfo> &i : javascript_class->properties) {
		p_properties->push_back(i.value);
	}
}

Variant::Type JavaScriptInstance::get_property_type(const StringName &p_name, bool *r_is_valid) const {
	*r_is_valid = false;
	if (javascript_class) {
		if (const JavaScriptProperyInfo *pi = javascript_class->properties.getptr(p_name)) {
			*r_is_valid = true;
			return pi->type;
		}
	}
	return Variant::NIL;
}

Variant JavaScriptInstance::callp(const StringName &p_method, const Variant **p_args, int p_argcount, Callable::CallError &r_error) {
	if (binder == NULL || javascript_object.javascript_object == NULL) {
		r_error.error = Callable::CallError::CALL_ERROR_INSTANCE_IS_NULL;
		ERR_FAIL_V(Variant());
	}
	if (binder->has_method(javascript_object, p_method)) {
		return binder->call_method(javascript_object, p_method, p_args, p_argcount, r_error);
	}
	return Variant();
}

ScriptLanguage *JavaScriptInstance::get_language() {
	return JavaScriptLanguage::get_singleton();
}

JavaScriptInstance::JavaScriptInstance() {
	owner = NULL;
	binder = NULL;
	javascript_class = NULL;
}

JavaScriptInstance::~JavaScriptInstance() {
	if (script.is_valid() && owner) {
		script->instances.erase(owner);
	}
}
