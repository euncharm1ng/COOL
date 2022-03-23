class A {
	a(): Int {1};
};

Class BB__ inherits A {
	c : String;
};

Class Ccc {
	hello(): Int {
		case true of
			y: Int => 3;
			z: String => 11;
			w: A => a();
		esac
	};
};

Class Iiiff {
	what_if(): Bool {
		if x = 1 THEN true else 
			{ if x = 2 Then true else false fi; }
		fi
	};
	try_let(a:Int, b:String, c:Int, d:Bool) : Int
		let temp:Int <- 2, temp22:Int <- 33 in (temp + temp22)
	};
};

