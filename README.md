# A Simple Calculator App for leaning C++

## Instructions
```bash
mkdir build
```
```bash
cd build; cmake ..
```
```bash
# If using a editor such as Neovim run this to enable completions in your LSP (clangd)
ln -s compile_commands.json ../
```

## Building
```bash
cd build; cmake --build .
```
From Josh's look over
```
Overall you have a good project structure and follow some good practices:

	- Using FetchContent to get fmt
	- Using fmt
	- Sorting your include headers and grouping local project ones 
	  at the top
	- Attempts to use c++ casts instead of c style casts
	- Consistent style/formatting
	- Code is clear and easy to follow

My review is purely from looking over the code. I haven't built or run it, so 
if I missed anything I apologize.

src/CMakeLists.txt
	Be careful with file globbing your source files on line 2:
	https://tinyurl.com/mutmjny5
	---
	For line 16 through 18, prefer using set_target_properties. The global
	CMAKE_CXX_STANDARD and CMAKE_CXX_STANDARD_REQUIRED properties affect all
	included CMake projects, which could cause issues. These properties are
	considered "old" CMake. Modern CMake uses target properties, which affect
	only the target:
	
		set_target_properties(calculator PROPERTIES
			CXX_STANDARD			20
			CXX_STANDARD_REQUIRED		TRUE)
	---
	In my CMake projects, I typically move the output directory to fall in
	line with CommSys practices, but in the open source world it's generally 
	considered a bad practice. Most cmake users will expect the resulting
	build artifacts to be output into the build directory.

	If you want to allow someone to specify the output directory, use a CMake 
	option() and default it to the default CMake location.
	---
	Since your project is an executable and not being consumed by anyone,
	consider changing your include directory to PRIVATE instead of PUBLIC.
	
	PRIVATE sets the directory include paths only for this target while PUBLIC
	will add them to any project that consumes your target (like a library).

	Prefer PRIVATE unless you know your target is meant to be consumed by
	an external project.

src/main.cpp
	You don't use the cctype, or fmt/core header files here, so you don't
	need to include them.

	Excess headers can lead to bloated compile times and unintended 
	dependencies.
	---
	It may be personal preference, but you can use auto on line 10:

		auto calc = std::make_unique<Calculator>();

	I used to be team hate auto, but as I've used it more my opinion has
	changed. It helps unclutter code, especially if templates are involved.
	---
	Typically hard coding numbers is a code smell and one should prefer named
	constants. However, one exception to this is the return from main. If you
	prefer named constants, you can include cstddef and then return EXIT_SUCCESS
	at the end of the function. I used to prefer the constant but got tired of
	including a whole header just for that, but I wanted to point it out as an
	option.

	Sticking with return 0 is fine, but if you ever need to return coded values
	to the operating system, switch to named constants in that program.


include/calculator.h
	You're not using cctype or fmt in the header file, so you can remove those
	includes
	---
	My first question when looking at the header is "Why is result a string and
	not a number type?"

	Some comments explaining the choice would be helpful. This is a situation
	where code should be self documenting, but comments are necessary to explain
	the "Why".
	---
	Since your constructors are defaulted and you don't have virtual or custom
	move/copy behavior, you can omit the constructor declarations (Rule Zero).

	Your declaration is already what the compiler adds by default.
	---
	Since the body of getResult() and getExpression() simply return their 
	respective variable values, you can inline them in the header. This gives
	the compiler a chance to better optimize the calls.

		std::string getResult() const
			{ return result; }

		std::string getExpression() const
			{ return expression; }

	For this small project, it's not a big deal. But larger complex projects where
	your functions could be called in a loop, the overhead of the function call
	can make a difference. When you inline, the compiler can remove this overhead.
	---
	Prefer using `const std::string&` as the return type to getResult() and 
	getExpression(). This will avoid unnecessary copies of the values when the
	functions are called because the compiler simply returns a const reference to 
	the underlying string.

	The compiler may optimize a copy out, but it'll probably miss more than it hits
	---
	You should declare getResult() and getExpression() as noexcept:

		const std::string& getResult() const noexcept
		const std::string& getExpression() const noexcept

	This keyword tells the compiler that the function will never throw an 
	exception and allows further optimizations.
	---
	You should consider also decorating getResult() and getExpression() with the
	[[nodiscard]] attribute:

		[[nodiscard]] const std::string& getResult() const noexcept
		[[nodiscard]] const std::string& getExpression() const noexcept

	This will result in a compiler warning if anyone accidentally calls these two
	functions without actually storing the return value. Unfortunately, this is
	why C++ is beginning to get a reputation for being verbose.
	---
	Consider taking std::string_view instead of const std::string& as the string
	parameter to all your public functions.

	std::string_view will point to the underlying character pointer and its length,
	regardless of the type of string (as long as the char types are the same).
	This prevents unnecessary generation/allocation that std::string can do if 
	someone were to call your function with a char const* (e.g. 
	evaluateExpression("4+1")).

	Prefer std::string_view as parameter types for strings. But, because it's
	non-owning of the string, avoid it as a return parameter without special 
	consideration.
	---
	The parseExpression, parseTerm, parseFactor, parseNumber, and skipWhitespace
	functions should be private since they're implementation details.

	Even better would be to remove them from the header entirely and write them
	in-line in an anonymous namespace in the cpp file:

		// Calculator.cpp
		namespace {
			void skipWhitespace(std::string_view expr, size_t& pos) {
				// ...
			}

			void parseExpression(std::string_view expr, size_t& pos) {
				// ...
			}

			// etc.
		}

		void Calculator::evaluateExpression(std::string_view expr) {
			// ...
		}

	This gets the implementation details out of the header. This isn't always easy
	if the private functions manipulate a bunch of the private state of the class.

	This also reduces recompilation if your implementation details change. You
	don't need to touch the header and only the Calculator.cpp file will need to
	be rebuilt.
	---
	Prefer avoiding in/out reference parameters if you can help it because they're 
	not easy to spot at the call site. At the call site, it looks like a normal
	function call and not immediately visible that pos is being modified.

	If you want an in-out parameter, use a pointer to make it clear to someone
	else reading the code at the call site that something is up:

		void skipWhitespace(std::string_view xpr, size_t* pos);
		skipWhitespace(expr, &pos); // The & is an attention grabber

	Or, better yet, return the new position instead. This is immediately clear
	how the function and pos parameters are related:

		size_t skipWhitespace(std::string_view expr, size_t pos);

		pos = skipWhitespace(expr, pos);

	It also allows the caller to control the return value, storing it in a 
	different variable if they need to perform some logical comparisons before 
	assigning


src/calculator.cpp
	For skipWhitespace, consider using std::isblank. std::isspace is fine, but
	just wanted to show an alternative. The difference is that isblank only
	considers space and tab while isspace considers any kind of whitespace such
    as line breaks.
	---
	For character functions that take an int, instead of using static_cast, use
	std::char_traits:

		using ctraits = std::char_traits<char>;

		void Calculator::skipWhitespace(const std::string &expr, size_t &pos) {
		  while(pos < expr.size() &&
		      std::isspace(ctraits::to_int_type(expr[pos]))) {
		    ++pos;
		  }
  		}

	If you ever need to go the other way, there's a from_int_type, too. For 
	example:

		auto lower_c = ctraits::from_int_type(std::tolower(
		  ctraits::to_int_type(c)));

	If I have to do this a lot, I'll put a little helpers in an anonymous namespace
	at the top of the file to keep code DRY:

		namespace {
		  using ctraits = std::char_traits<char>;

		  bool is_space(char c) noexecpt {
		    return std::isblank(ctraits::to_int_type(c));
		  }

		  bool is_digit(char c) noexcept {
		    return std::isdigit(ctraits::to_int_type(c));
		  }
		}
	---

From here, my suggestions are:

1) Add support for real numbers, scientific notation, roots, and exponents. Don't forget expressions that result in NaN or infinity.

2) Add more detailed error messages like "Error in expression at N" where N is the character index the error occurred. Consider displaying a compiler like error that draws the expression and an arrow pointing to the error. Custom exception types will be helpful here.

3) Advanced: Split the implementation into a tokenizer/lexer, parser, and evaluator. A postfix (reverse polish notation) workflow will help you with the evaluator. Rather than RPN, you could try an Abstract Syntax Tree, but these are pretty advanced to setup and evaluate. My suggestion is use RPN for now.
```
```
