//**************************************************************
//
// Code generator SKELETON
//
// Read the comments carefully and add code to build an LLVM program 
//**************************************************************

#define EXTERN
#include "cgen.h"
#include <string>
#include <sstream>

// 
extern int cgen_debug;

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.  Feel free to add your
// own definitions as you see fit.
//
//////////////////////////////////////////////////////////////////////
EXTERN Symbol 
	// required classes
	Object,
	IO,
	String,
	Int,
	Bool,
	Main,

	// class methods
	cool_abort,
	type_name,
	cool_copy,
	out_string,
	out_int,
	in_string,
	in_int,
	length,
	concat,
	substr,

	// class members
	val,

	// special symbols
	No_class,    // symbol that can't be the name of any user-defined class
	No_type,     // If e : No_type, then no code is generated for e.
	SELF_TYPE,   // Special code is generated for new SELF_TYPE.
	self,        // self generates code differently than other references

	// extras
	arg,
	arg2,
	prim_string,
	prim_int,
	prim_bool;


//********************************************************
//
// PREDEFINED FUNCTIONS:
//
// The following functions are already coded, you should
// not need to modify them, although you may if necessary.
//
//********************************************************

//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
	Object      = idtable.add_string("Object");
	IO          = idtable.add_string("IO");
	String      = idtable.add_string("String");
	Int         = idtable.add_string("Int");
	Bool        = idtable.add_string("Bool");
	Main        = idtable.add_string("Main");

	cool_abort  = idtable.add_string("abort");
	type_name   = idtable.add_string("type_name");
	cool_copy   = idtable.add_string("copy");
	out_string  = idtable.add_string("out_string");
	out_int     = idtable.add_string("out_int");
	in_string   = idtable.add_string("in_string");
	in_int      = idtable.add_string("in_int");
	length      = idtable.add_string("length");
	concat      = idtable.add_string("concat");
	substr      = idtable.add_string("substr");

	val         = idtable.add_string("val");

	No_class    = idtable.add_string("_no_class");
	No_type     = idtable.add_string("_no_type");
	SELF_TYPE   = idtable.add_string("SELF_TYPE");
	self        = idtable.add_string("self");

	arg         = idtable.add_string("arg");
	arg2        = idtable.add_string("arg2");
	prim_string = idtable.add_string("sbyte*");
	prim_int    = idtable.add_string("int");
	prim_bool   = idtable.add_string("bool");
}

//*********************************************************
//
// Define method for code generation
//
// This is the method called by the compiler driver
// `cgtest.cc'. cgen takes an `ostream' to which the assembly will be
// emitted, and it passes this and the class list of the
// code generator tree to the constructor for `CgenClassTable'.
// That constructor performs all of the work of the code
// generator.
//
//*********************************************************
void program_class::cgen(ostream &os) 
{
	initialize_constants();
	class_table = new CgenClassTable(classes,os);
}


// Create definitions for all String constants
void StrTable::code_string_table(ostream& s, CgenClassTable* ct)
{
	for (List<StringEntry> *l = tbl; l; l = l->tl()) {
		l->hd()->code_def(s, ct);
	}
}

// Create definitions for all Int constants
void IntTable::code_string_table(ostream& s, CgenClassTable* ct)
{
	for (List<IntEntry> *l = tbl; l; l = l->tl()) {
		l->hd()->code_def(s, ct);
	}
}

//
// Sets up declarations for extra functions needed for code generation
// You should not need to modify this code for PA5
//
void CgenClassTable::setup_external_functions()
{
	ValuePrinter vp;
	// setup function: external int strcmp(sbyte*, sbyte*)
	op_type i32_type(INT32), i8ptr_type(INT8_PTR), vararg_type(VAR_ARG);
	vector<op_type> strcmp_args;
	strcmp_args.push_back(i8ptr_type);
	strcmp_args.push_back(i8ptr_type);	
	vp.declare(*ct_stream, i32_type, "strcmp", strcmp_args); 

	// setup function: external int printf(sbyte*, ...)
	vector<op_type> printf_args;
	printf_args.push_back(i8ptr_type);
	printf_args.push_back(vararg_type);
	vp.declare(*ct_stream, i32_type, "printf", printf_args);

	// setup function: external void abort(void)
	op_type void_type(VOID);
	vector<op_type> abort_args;
	vp.declare(*ct_stream, void_type, "abort", abort_args);

	// setup function: external i8* malloc(i32)
	vector<op_type> malloc_args;
	malloc_args.push_back(i32_type);
	vp.declare(*ct_stream, i8ptr_type, "malloc", malloc_args);

#ifdef PA5
	//ADD CODE HERE
	//Setup external functions for built in object class functions
#endif
}

// Creates AST nodes for the basic classes and installs them in the class list
void CgenClassTable::install_basic_classes()
{
	// The tree package uses these globals to annotate the classes built below.
	curr_lineno = 0;
	Symbol filename = stringtable.add_string("<basic class>");

	//
	// A few special class names are installed in the lookup table but not
	// the class list. Thus, these classes exist, but are not part of the
	// inheritance hierarchy.
	 
	// No_class serves as the parent of Object and the other special classes.
	Class_ noclasscls = class_(No_class,No_class,nil_Features(),filename);
	install_special_class(new CgenNode(noclasscls, CgenNode::Basic, this));
	delete noclasscls;

#ifdef PA5
	// SELF_TYPE is the self class; it cannot be redefined or inherited.
	Class_ selftypecls = class_(SELF_TYPE,No_class,nil_Features(),filename);
	install_special_class(new CgenNode(selftypecls, CgenNode::Basic, this));
	delete selftypecls;
	// 
	// Primitive types masquerading as classes. This is done so we can
	// get the necessary Symbols for the innards of String, Int, and Bool
	//
	Class_ primstringcls = class_(prim_string,No_class,nil_Features(),filename);
	install_special_class(new CgenNode(primstringcls, CgenNode::Basic, this));
	delete primstringcls;
#endif
	Class_ primintcls = class_(prim_int,No_class,nil_Features(),filename);
	install_special_class(new CgenNode(primintcls, CgenNode::Basic, this));
	delete primintcls;
	Class_ primboolcls = class_(prim_bool,No_class,nil_Features(),filename);
	install_special_class(new CgenNode(primboolcls, CgenNode::Basic, this));
	delete primboolcls;
	// 
	// The Object class has no parent class. Its methods are
	//        cool_abort() : Object   aborts the program
	//        type_name() : Str       returns a string representation of class name
	//        copy() : SELF_TYPE      returns a copy of the object
	//
	// There is no need for method bodies in the basic classes---these
	// are already built in to the runtime system.
	//
	Class_ objcls =
		class_(Object, 
		       No_class,
		       append_Features(
		       append_Features(
		       single_Features(method(cool_abort, nil_Formals(), 
		                              Object, no_expr())),
		       single_Features(method(type_name, nil_Formals(),
		                              String, no_expr()))),
		       single_Features(method(cool_copy, nil_Formals(), 
		                              SELF_TYPE, no_expr()))),
		       filename);
	install_class(new CgenNode(objcls, CgenNode::Basic, this));
	delete objcls;

//
// The Int class has no methods and only a single attribute, the
// "val" for the integer. 
//
	Class_ intcls=
		class_(Int, 
		       Object,
		       single_Features(attr(val, prim_int, no_expr())),
		       filename);
	install_class(new CgenNode(intcls, CgenNode::Basic, this));
	delete intcls;

//
// Bool also has only the "val" slot.
//
	Class_ boolcls=
		class_(Bool,  
		       Object, 
		       single_Features(attr(val, prim_bool, no_expr())),
		       filename);
	install_class(new CgenNode(boolcls, CgenNode::Basic, this));
	delete boolcls;

#ifdef PA5
//
// The class String has a number of slots and operations:
//       val                                  the string itself
//       length() : Int                       length of the string
//       concat(arg: Str) : Str               string concatenation
//       substr(arg: Int, arg2: Int): Str     substring
//       
	Class_ stringcls =
		class_(String, 
		       Object,
		       append_Features(
		       append_Features(
		       append_Features(
		       single_Features(attr(val, prim_string, no_expr())),
		       single_Features(method(length, nil_Formals(),
		                              Int, no_expr()))),
		       single_Features(method(concat,
		                              single_Formals(formal(arg, String)),
		                              String,
		                              no_expr()))),
		       single_Features(method(substr, 
		                              append_Formals(
		                                 single_Formals(formal(arg, Int)), 
		                                 single_Formals(formal(arg2, Int))),
		                              String, 
		                              no_expr()))),
		       filename);
	install_class(new CgenNode(stringcls, CgenNode::Basic, this));
	delete stringcls;
#endif

#ifdef PA5
// 
// The IO class inherits from Object. Its methods are
//        out_string(Str) : SELF_TYPE          writes a string to the output
//        out_int(Int) : SELF_TYPE               "    an int    "  "     "
//        in_string() : Str                    reads a string from the input
//        in_int() : Int                         "   an int     "  "     "
//
	Class_ iocls =
		class_(IO,
		       Object,
		       append_Features(
		       append_Features(
		       append_Features(
		       single_Features(method(out_string,
		                              single_Formals(formal(arg, String)),
		                              SELF_TYPE, no_expr())),
		       single_Features(method(out_int, single_Formals(formal(arg, Int)),
		                              SELF_TYPE, no_expr()))),
		       single_Features(method(in_string, nil_Formals(), String,
		                              no_expr()))),
		       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
		       filename);
	install_class(new CgenNode(iocls, CgenNode::Basic, this));
	delete iocls;
#endif
}

//
// install_classes enters a list of classes in the symbol table.
//
void CgenClassTable::install_classes(Classes cs)
{
	for (int i = cs->first(); cs->more(i); i = cs->next(i)) {
		install_class(new CgenNode(cs->nth(i),CgenNode::NotBasic,this));
	}
}

// 
// Add this CgenNode to the class list and the lookup table
// 
void CgenClassTable::install_class(CgenNode *nd)
{
	Symbol name = nd->get_name();

	if (probe(name))
		return;

	// The class name is legal, so add it to the list of classes
	// and the symbol table.
	nds = new List<CgenNode>(nd,nds);
	addid(name,nd);
}

// 
// Add this CgenNode to the special class list and the lookup table
// 
void CgenClassTable::install_special_class(CgenNode *nd)
{
	Symbol name = nd->get_name();

	if (probe(name))
		return;

	// The class name is legal, so add it to the list of special classes
	// and the symbol table.
	special_nds = new List<CgenNode>(nd, special_nds);
	addid(name,nd);
}

//
// CgenClassTable::build_inheritance_tree
//
void CgenClassTable::build_inheritance_tree()
{
	for(List<CgenNode> *l = nds; l; l = l->tl())
		set_relations(l->hd());
}

//
// CgenClassTable::set_relations
//
// Takes a CgenNode and locates its, and its parent's, inheritance nodes
// via the class table.  Parent and child pointers are added as appropriate.
//
void CgenClassTable::set_relations(CgenNode *nd)
{
	CgenNode *parent_node = probe(nd->get_parent());
	nd->set_parentnd(parent_node);
	parent_node->add_child(nd);
}

// Get the root of the class tree.
CgenNode *CgenClassTable::root()
{
	return probe(Object);
}

//////////////////////////////////////////////////////////////////////
//
// Special-case functions used for the method Int Main::main() for
// PA5 only.
//
//////////////////////////////////////////////////////////////////////

#ifndef PA5

CgenNode* CgenClassTable::getMainmain(CgenNode* c)
{
	if (c && ! c->basic())
		return c;                   // Found it!

	List<CgenNode> *children = c->get_children();
	for (List<CgenNode> *child = children; child; child = child->tl()) {
		if (CgenNode* foundMain = this->getMainmain(child->hd()))
			return foundMain;   // Propagate it up the recursive calls
	}

	return 0;                           // Make the recursion continue
}

#endif

//-------------------------------------------------------------------
//
// END OF PREDEFINED FUNCTIONS
//
//-------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////
//
// coding string, int, and boolean constants
//
// Cool has three kinds of constants: strings, ints, and booleans.
// This section defines code generation for each type.
//
// All string constants are listed in the global "stringtable" and have
// type stringEntry.  stringEntry methods are defined both for string
// constant definitions and references.
//
// All integer constants are listed in the global "inttable" and have
// type IntEntry.  IntEntry methods are defined for Int
// constant definitions and references.
//
// Since there are only two Bool values, there is no need for a table.
// The two booleans are represented by instances of the class BoolConst,
// which defines the definition and reference methods for Bools.
//
///////////////////////////////////////////////////////////////////////////////

//
// Create global definitions for constant Cool objects
//
void CgenClassTable::code_constants()
{
#ifdef PA5
	// ADD CODE HERE
#endif
}

// generate code to define a global string constant
void StringEntry::code_def(ostream& s, CgenClassTable* ct)
{
#ifdef PA5
	// ADD CODE HERE
#endif
}

// generate code to define a global int constant
void IntEntry::code_def(ostream& s, CgenClassTable* ct)
{
	// Leave this method blank, since we are not going to use global
	// declarations for int constants.
}

//////////////////////////////////////////////////////////////////////////////
//
//  CgenClassTable methods
//
//////////////////////////////////////////////////////////////////////////////

//
// CgenClassTable constructor orchestrates all code generation
//
CgenClassTable::CgenClassTable(Classes classes, ostream& s) 
: nds(0)
{
	if (cgen_debug) std::cerr << "Building CgenClassTable" << endl;
	ct_stream = &s;
	// Make sure we have a scope, both for classes and for constants
	enterscope();

	// Create an inheritance tree with one CgenNode per class.
	install_basic_classes();
	install_classes(classes);
	build_inheritance_tree();

	// First pass
	setup();

	// Second pass
	code_module();

	// Done with code generation: exit scopes
	exitscope();
}

CgenClassTable::~CgenClassTable()
{
}

// The code generation first pass.  Define these two functions to traverse
// the tree and setup each CgenNode
void CgenClassTable::setup()
{
	setup_external_functions();
	setup_classes(root(), 0);
}


void CgenClassTable::setup_classes(CgenNode *c, int depth)
{
	// MAY ADD CODE HERE
	// if you want to give classes more setup information

	c->setup(current_tag++, depth);
	List<CgenNode> *children = c->get_children();
	for (List<CgenNode> *child = children; child; child = child->tl())
		setup_classes(child->hd(), depth + 1);
	
	c->set_max_child(current_tag-1);

	/*
	if (cgen_debug)
		std::cerr << "Class " << c->get_name() << " assigned tag " 
			<< c->get_tag() << ", max child " << c->get_max_child() 
			<< ", depth " << c->get_depth() << endl;
	*/
}


// The code generation second pass. Add code here to traverse the tree and
// emit code for each CgenNode
void CgenClassTable::code_module()
{
	code_constants();

#ifndef PA5
	// This must be after code_module() since that emits constants
	// needed by the code() method for expressions
	CgenNode* mainNode = getMainmain(root());
	mainNode->codeGenMainmain();
#endif
	code_main();

#ifdef PA5
	code_classes(root());
#else
#endif
}


#ifdef PA5
void CgenClassTable::code_classes(CgenNode *c)
{

	// ADD CODE HERE

}
#endif


//
// Create LLVM entry point. This function will initiate our Cool program 
// by generating the code to execute (new Main).main()
//
void CgenClassTable::code_main()
{
	ValuePrinter vp(*ct_stream);
	op_type i32_type(INT32);
	op_type i8_ptr(INT8_PTR);
	op_type varArg(VAR_ARG);
	vector<op_type> main_args_types;
	vector<operand> main_args;
	string main_entry("entry");

	// to match the lab pt specification
	string print_format("%d");
	op_arr_type array_type(INT8, print_format.length()+1);
	const_value strConst(array_type, print_format, false);
	vp.init_constant(".str", strConst);

	vp.define(i32_type, "main", main_args);
	vp.begin_block(main_entry);

	// Call Main_main(). This returns int* for phase 1, Object for phase 2
	operand result = vp.call(main_args_types, i32_type, "Main_main", true, main_args);

#ifndef PA5
	// Get the address of the string "Main_main() returned %d\n" using getelementptr 
	vector<op_type> printf_args_types;
	vector<operand> printf_args;

	op_arr_type string_type(INT8_PTR, print_format.length()+1);
	global_value ptr_string(string_type, ".str", strConst);
	operand pointer = vp.getelementptr(array_type, ptr_string, int_value(0), int_value(0), i8_ptr);

	// Call printf with the string address of "Main_main() returned %d\n"
	// and the return value of Main_main() as its arguments
	printf_args_types.push_back(i8_ptr);
	printf_args_types.push_back(varArg);
	printf_args.push_back(pointer);
	printf_args.push_back(result);
	vp.call(printf_args_types, i32_type, "printf", true, printf_args);

	vp.ret(int_value(0));

#else
	// Phase 2
#endif
	vp.end_define();
}


///////////////////////////////////////////////////////////////////////
//
// CgenNode methods
//
///////////////////////////////////////////////////////////////////////

CgenNode::CgenNode(Class_ nd, Basicness bstatus, CgenClassTable *ct)
: class__class((const class__class &) *nd), 
  parentnd(0), children(0), basic_status(bstatus), class_table(ct), tag(-1)
{ 
	// ADD CODE HERE
}

void CgenNode::add_child(CgenNode *n)
{
	children = new List<CgenNode>(n,children);
}

void CgenNode::set_parentnd(CgenNode *p)
{
	assert(parentnd == NULL);
	assert(p != NULL);
	parentnd = p;
}

//
// Class setup.  You may need to add parameters to this function so that
// the classtable can provide setup information (such as the class tag
// that should be used by this class).  
// 
// Things that setup should do:
//  - layout the features of the class
//  - create the types for the class and its vtable
//  - create global definitions used by the class such as the class vtable
//
void CgenNode::setup(int tag, int depth)
{
	this->tag = tag;
#ifdef PA5
	layout_features();

	// ADD CODE HERE

#endif
}

#ifdef PA5
//
// Class codegen. This should performed after every class has been setup.
// Generate code for each method of the class.
//
void CgenNode::code_class()
{
	// No code generation for basic classes. The runtime will handle that.
	if (basic())
		return;
	
	// ADD CODE HERE
}

// Laying out the features involves creating a Function for each method
// and assigning each attribute a slot in the class structure.
void CgenNode::layout_features()
{
	// ADD CODE HERE
}
#else

// 
// code-gen function main() in class Main
//
void CgenNode::codeGenMainmain()
{
	ValuePrinter vp(*get_classtable()->ct_stream);
	// In Phase 1, this can only be class Main. Get method_class for main().
	assert(std::string(this->name->get_string()) == std::string("Main"));
	method_class* mainMethod = (method_class*) features->nth(features->first());

	// ADD CODE HERE TO GENERATE THE FUNCTION int Mainmain().
	// Generally what you need to do are:
	// -- setup or create the environment, env, for translating this method
	// -- invoke mainMethod->code(env) to translate the method
	
	CgenEnvironment *env = new CgenEnvironment(*get_classtable()->ct_stream, this);
	vector<operand> main_args;
	op_type i32_type(INT32);
	vp.define(i32_type, "Main_main", main_args);
	//vp.begin_block("entry");
	mainMethod->code(env);
	vp.end_define();
}

#endif

///////////////////////////////////////////////////////////////////////
//
// CgenEnvironment functions
//
///////////////////////////////////////////////////////////////////////

//
// Class CgenEnvironment should be constructed by a class prior to code
// generation for each method.  You may need to add parameters to this
// constructor.
//
CgenEnvironment::CgenEnvironment(std::ostream &o, CgenNode *c)
{
	cur_class = c;
	cur_stream = &o;
	var_table.enterscope();
	tmp_count = block_count = ok_count = 0;
	// ADD CODE HERE
}

// Look up a CgenNode given a symbol
CgenNode *CgenEnvironment::type_to_class(Symbol t) {
	return t == SELF_TYPE ? get_class() 
		: get_class()->get_classtable()->lookup(t);
}

// Provided CgenEnvironment methods
// Generate unique string names
std::string CgenEnvironment::new_name() {
	std::stringstream s;
	s << tmp_count++;
	return "tmp." + s.str();
}

std::string CgenEnvironment::new_ok_label() {
	std::stringstream s;
	s << ok_count++;
	return "ok." + s.str();
}
const std::string CgenEnvironment::new_label(const std::string& prefix,
		bool increment) {
	std::string suffix = itos(block_count);
	block_count += increment;
	return prefix + suffix;
}

void CgenEnvironment::add_local(Symbol name, operand &vb) {
	var_table.enterscope();
	var_table.addid(name, &vb);
}

void CgenEnvironment::kill_local() {
	var_table.exitscope();
}


////////////////////////////////////////////////////////////////////////////
//
// APS class methods
//
////////////////////////////////////////////////////////////////////////////

//******************************************************************
//
//   Fill in the following methods to produce code for the
//   appropriate expression.  You may add or remove parameters
//   as you wish, but if you do, remember to change the parameters
//   of the declarations in `cool-tree.handcode.h'.
//
//*****************************************************************

#ifdef PA5
// conform and get_class_tag are only needed for PA5

// conform - If necessary, emit a bitcast or boxing/unboxing operations
// to convert an object to a new type. This can assume the object
// is known to be (dynamically) compatible with the target type.
// It should only be called when this condition holds.
// (It's needed by the supplied code for typecase)
operand conform(operand src, op_type type, CgenEnvironment *env) {
	// ADD CODE HERE (PA5 ONLY)
	return operand();
}

// Retrieve the class tag from an object record.
// src is the object we need the tag from.
// src_class is the CgenNode for the *static* class of the expression.
// You need to look up and return the class tag for it's dynamic value
operand get_class_tag(operand src, CgenNode *src_cls, CgenEnvironment *env) {
	// ADD CODE HERE (PA5 ONLY)
	return operand();
}
#endif

//
// Create a method body
// 
void method_class::code(CgenEnvironment *env)
{
	if (cgen_debug) std::cerr << "method" << endl;
	ValuePrinter vp(*env->cur_stream);

	vp.ret(expr->code(env));
}

//
// Codegen for expressions.  Note that each expression has a value.
//

operand assign_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "assign" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand new_value = expr->code(env);
	operand var = *env->lookup(name);

	vp.store(new_value, var);
	return new_value;
}

operand cond_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "cond" << endl;
	ValuePrinter vp(*env->cur_stream);
	string then_br = env->new_label("cond.", true);
	string else_br = env->new_label("cond.", true);
	string end_br = env->new_label("cond.", true);
	//FIXME, any other way to get the type without running the code?
	operand merge = vp.alloca_mem(then_exp->code(env).get_type());

	operand pred_operand = pred->code(env);

	vp.branch_cond(pred_operand, then_br, else_br);

	vp.begin_block(then_br);
	operand then_operand = then_exp->code(env);
	vp.store(then_operand, merge);
	vp.branch_uncond(end_br);

	vp.begin_block(else_br);
	operand else_operand = else_exp->code(env);
	vp.store(else_operand, merge);
	vp.branch_uncond(end_br);

	vp.begin_block(end_br);

	return vp.load(else_operand.get_type(), merge);
}

operand loop_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "loop" << endl;
	ValuePrinter vp(*env->cur_stream);
	string loop_br = env->new_label("loop.", true);
	string body_br = env->new_label("loop.", true);
	string end_br = env->new_label("loop.", true);

	vp.branch_uncond(loop_br);
	vp.begin_block(loop_br);
	operand pred_operand = pred->code(env);
	vp.branch_cond(pred_operand, body_br, end_br);

	vp.begin_block(body_br);
	operand body_operand = body->code(env);
	vp.branch_uncond(loop_br);

	vp.begin_block(end_br);
	return body_operand;
} 

operand block_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "block" << endl;
	operand last_operand;
	for(int i = body->first(); body->more(i); i = body->next(i)){
		last_operand = body->nth(i)->code(env);
	}
	return last_operand;
}

operand let_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "let" << endl;
	ValuePrinter vp(*env->cur_stream);
	op_type var_type;
	string type_str(type_decl->get_string());

	if(type_str.compare("Bool") == 0) var_type = INT1;
	else var_type = INT32;

	operand var_alloca = vp.alloca_mem(var_type);
	env->add_local(identifier, var_alloca);

	operand var_val = init->code(env);
	if(var_val.get_type().get_id() == EMPTY){
		string _val;
		if(var_type.get_id() == INT1) _val = "false";
		else if(var_type.get_id() == INT32) _val = "0";
		vp.store(const_value(var_type, _val, false), var_alloca);
	}
	else vp.store(var_val, var_alloca);
	return body->code(env);
}

operand plus_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "plus" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand e1_operand = e1->code(env);
	operand e2_operand = e2->code(env);
	return vp.add(e1_operand, e2_operand);
}

operand sub_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "sub" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand e1_operand = e1->code(env);
	operand e2_operand = e2->code(env);
	return vp.sub(e1_operand, e2_operand);
}

operand mul_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "mul" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand e1_operand = e1->code(env);
	operand e2_operand = e2->code(env);
	return vp.mul(e1_operand, e2_operand);
}

operand divide_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "div" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand e1_operand = e1->code(env);
	operand e2_operand = e2->code(env);
	return vp.div(e1_operand, e2_operand);
}

operand neg_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "neg" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand e1_operand = e1->code(env);
	return vp.sub(int_value(0), e1_operand);
}

operand lt_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "lt" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand e1_operand = e1->code(env);
	operand e2_operand = e2->code(env);
	return vp.icmp(LT, e1_operand, e2_operand);
}

operand eq_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "eq" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand e1_operand = e1->code(env);
	operand e2_operand = e2->code(env);
	return vp.icmp(EQ, e1_operand, e2_operand);
}

operand leq_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "leq" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand e1_operand = e1->code(env);
	operand e2_operand = e2->code(env);
	return vp.icmp(LE, e1_operand, e2_operand);
}

operand comp_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "complement" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand e1_operand = e1->code(env);
	return vp.xor_in(e1_operand, bool_value(true, 0));
}

operand int_const_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "Integer Constant" << endl;
	return int_value(atoi(token->get_string()));
}

operand bool_const_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "Boolean Constant" << endl;
	return bool_value(val, 0);
}

operand object_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "Object" << endl;
	ValuePrinter vp(*env->cur_stream);
	operand obj = *env->lookup(name);
	return vp.load(obj.get_type().get_deref_type(), obj);
}

operand no_expr_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "No_expr" << endl;
	// ADD CODE HERE AND REPLACE "return operand()" WITH SOMETHING 
	// MORE MEANINGFUL
	return operand();
}

//*****************************************************************
// The next few functions are for node types not supported in Phase 1
// but these functions must be defined because they are declared as
// methods via the Expression_SHARED_EXTRAS hack.
//*****************************************************************

operand static_dispatch_class::code(CgenEnvironment *env) 
{ 
	if (cgen_debug) std::cerr << "static dispatch" << endl;
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE AND REPLACE "return operand()" WITH SOMETHING 
	// MORE MEANINGFUL
#endif
	return operand();
}

operand string_const_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "string_const" << endl;
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE AND REPLACE "return operand()" WITH SOMETHING 
	// MORE MEANINGFUL
#endif
	return operand();
}

operand dispatch_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "dispatch" << endl;
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE AND REPLACE "return operand()" WITH SOMETHING 
	// MORE MEANINGFUL
#endif
	return operand();
}

operand typcase_class::code(CgenEnvironment *env)
{
	if (cgen_debug) 
		std::cerr << "typecase::code()" << endl;
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE AND REPLACE "return operand()" WITH SOMETHING 
	// MORE MEANINGFUL
#endif
	return operand();
}

operand new__class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "newClass" << endl;
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE AND REPLACE "return operand()" WITH SOMETHING 
	// MORE MEANINGFUL
#endif
	return operand();
}

operand isvoid_class::code(CgenEnvironment *env) 
{
	if (cgen_debug) std::cerr << "isvoid" << endl;
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE AND REPLACE "return operand()" WITH SOMETHING 
	// MORE MEANINGFUL
#endif
	return operand();
}

// Create the LLVM Function corresponding to this method.
void method_class::layout_feature(CgenNode *cls) 
{
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE
#endif
}

// If the source tag is >= the branch tag and <= (max child of the branch class) tag,
// then the branch is a superclass of the source
operand branch_class::code(operand expr_val, operand tag,
				op_type join_type, CgenEnvironment *env) {
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE AND REPLACE "return operand()" WITH SOMETHING 
	// MORE MEANINGFUL
#endif
	return operand();
}

// Assign this attribute a slot in the class structure
void attr_class::layout_feature(CgenNode *cls)
{
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE
#endif
}

void attr_class::code(CgenEnvironment *env)
{
#ifndef PA5
	assert(0 && "Unsupported case for phase 1");
#else
	// ADD CODE HERE
#endif
}

