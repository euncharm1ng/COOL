for file in *
do
	if [[ $file = *".cl" ]]
	then
		echo $file
		./answer_lexer $file | ./parser
		echo ------------------------------------------
		./answer_lexer $file | ./answer_parser
		echo +++++++++++++++++++++++++++++++++++++++++++++++++
	fi
done
