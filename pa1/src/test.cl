ClAsS MyClass iNHeriTS YourClass {
	myVar : Int <- 100 ;

	init() : MyClass { self } ;

	getVar() : Int { myVar } ;
}

cLaSs YourClass {
	veryLongString: String <- "asdf\
	asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdf" ;

	init() : YourClass { self } ;

	getVeryLongString() : String { veryLongString } ;
}

CLAss Main {
	my : MyClass <- (new MyClass).init() ;
	your : YourClass <- (new YourClass).init() ;
	main() : Object {
		let var : Int <- my.getVar(),
			aVeryLongString : String <- your.getVeryLongString(),
			sum = var + aVeryLongString.length() in {

			out_int(sum) ;
		}
	} ;
}
-- The length of this string is (* 1024 *)\
"1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
"
-- The length of this string is (* (* 1025\
"1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
X"

-- The length of this unterminated string is (* (* 1025\
"1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
X

-- a long string that contains multiple nulls
"1234567890abcde\
 1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abcde\
1234567890abc de\
1234567890 abcde\
1234567 890abcde\
1234 567890abcde\
1 234567890abcde\
 "

-- Null in a string
"1234 5\
67890"

-- multiple Nulls in a string
"four    nulls"

-- Null in an unterminated string
"1234 5

-- escaped Null in a string
"aaaa\ aaaa"

-- Null
 

(* This (** is (*** a (****nested(***** comment*****)****) \
***) closing **) comment... *)

*) this is an unmatched Comment &

`1234567890-=qwertyuiop[]\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:ZXCVBNM<>?


-- (* uncomment this for EOF in comment
"or uncomment this for EOF in string\
