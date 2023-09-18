/**************************************************************************/
/*  quickjs_callable.h                                                    */
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

#ifndef QUICKJS_CALLABLE_H
#define QUICKJS_CALLABLE_H

#include "../javascript_callable.h"
#include "quickjs/quickjs.h"

#if !defined(JS_NAN_BOXING)
///typedef uint64_t JSValue; defined in quickjs.h if defined(JS_NAN_BOXING)
struct JSValue;
#endif

class QuickJSCallable : public JavaScriptCallable {
	static bool compare_equal(const CallableCustom *p_a, const CallableCustom *p_b);
	static bool compare_less(const CallableCustom *p_a, const CallableCustom *p_b);

public:
	QuickJSCallable(JSContext *ctx, const JSValue &p_value);
	QuickJSCallable(const JavaScriptGCHandler &p_function);
	virtual ~QuickJSCallable();

	virtual uint32_t hash() const override;
	virtual String get_as_text() const override;

	virtual CompareEqualFunc get_compare_equal_func() const override { return QuickJSCallable::compare_equal; }
	virtual CompareLessFunc get_compare_less_func() const override { return QuickJSCallable::compare_less; }

	virtual ObjectID get_object() const override;
	virtual void call(const Variant **p_arguments, int p_argcount, Variant &r_return_value, Callable::CallError &r_call_error) const override;
};

#endif // QUICKJS_CALLABLE_H
