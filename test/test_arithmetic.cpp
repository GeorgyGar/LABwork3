// тесты для вычисления арифметических выражений

#include <gtest.h>
#include <arithmetic.h>

TEST(Lexema, can_create_Lexem)
{
	ASSERT_NO_THROW(Lexema L);
}

TEST(Lexema, Equality)
{
	string V = "*";
	Lexema Le(V);
	ASSERT_EQ(Le.Val, "*");
}

TEST(Lexema, not_Equality)
{
	string V = "-";
	Lexema Le(V);
	ASSERT_NE(Le.Val, "+");
}

TEST(Lexema, can_create_copy_1)
{
	string V = "-";
	Lexema Le(V);
	ASSERT_NO_THROW(Lexema L(Le));
}

TEST(Lexema, can_create_copy_2)
{
	string V = "-";
	Lexema Le(V);
	Lexema L(Le);
	ASSERT_EQ(Le.Val,L.Val);
}

TEST(Lexema, forbidden_Lexema_1)
{
	string V = ":";
	ASSERT_ANY_THROW(Lexema L(V));
}

TEST(Lexema, forbidden_Lexema_2)
{
	string V = "$$%";
	ASSERT_ANY_THROW(Lexema L(V));
}

TEST(arithmetic, can_create_arithmetic)
{
	string Primer = "(5+5))";
	ASSERT_NO_THROW(arithmetic arith(Primer));
}


TEST(arithmetic, check_parenthesis_1)
{
	string Primer = "(5+5))";
	arithmetic arith(Primer);
	ASSERT_ANY_THROW(arith.Check());
}

TEST(arithmetic, check_parenthesis_2)
{
	string Primer = ")(5+5))";
	arithmetic arith(Primer);
	ASSERT_ANY_THROW(arith.Check());
}

TEST(arithmetic, check_parenthesis_3)
{
	string Primer = "5-(5+3(";
	arithmetic arith(Primer);
	ASSERT_ANY_THROW(arith.Check());
}

TEST(arithmetic, checking_for_characters)
{
	string Primer = "(5+?9)";
	arithmetic arith(Primer);
	ASSERT_ANY_THROW(arith.BreakLexemes());
}

TEST(arithmetic, incorrect_Lexema_1)
{
	string Primer = "5+$5";
	arithmetic arith(Primer);
	ASSERT_ANY_THROW(arith.BreakLexemes());
}

TEST(arithmetic, incorrect_Lexema_2)
{
	string Primer = "(5+6*(9&+2))";
	arithmetic arith(Primer);
	ASSERT_ANY_THROW(arith.BreakLexemes());
}

TEST(arithmetic, Unary_minus_1)
{
	string Primer = "5+(-2)";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(3, arith.PolishLexemesSolution());
}

TEST(arithmetic, Unary_minus_2)
{
	string Primer = "8,5+-6,2";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(2.3, arith.PolishLexemesSolution());
}

TEST(arithmetic, Unary_minus_3)
{
	string Primer = "5+2*(6--8*2)";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(49, arith.PolishLexemesSolution());
}

TEST(arithmetic, Unary_minus_4)
{
	string Primer = "-8+9*-5";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(-53, arith.PolishLexemesSolution()); 
}

TEST(arithmetic, Unary_plus_1)
{
	string Primer = "5++5";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(10, arith.PolishLexemesSolution()); 
}

TEST(arithmetic, Unary_plus_2)
{
	string Primer = "+2,2*2";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(4.4, arith.PolishLexemesSolution());
}

TEST(arithmetic, incorrect_input)
{
	string Primer = "5*/8";
	arithmetic arith(Primer);
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_ANY_THROW(arith.PolishLexemesSolution());
}

TEST(arithmetic, free_entry)
{
	string Primer = "5.5+1,8";
	arithmetic arith(Primer);
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(7.3,arith.PolishLexemesSolution());
}

TEST(arithmetic, can_use_a_space_1)
{
	string Primer = "5.5+ 1,8";
	arithmetic arith(Primer);
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(7.3, arith.PolishLexemesSolution());
}

TEST(arithmetic, can_use_a_space_2)
{
	string Primer = "5 + 2* 3";
	arithmetic arith(Primer);
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(11, arith.PolishLexemesSolution());
}

TEST(arithmetic, example_1)
{
	string Primer = "5*(6+25)";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(155, (arith.PolishLexemesSolution()));
}

TEST(arithmetic, example_2)
{
	string Primer = "5,6* 5,7/8";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(4, round(arith.PolishLexemesSolution()));
}

TEST(arithmetic, example_3)
{
	string Primer = "5,78 +12*( 1,2 /8)- (12,6+5/5)";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(-6, round(arith.PolishLexemesSolution()));
}

TEST(arithmetic, example_4)
{
	string Primer = "(5,123-(2,56*(12,3/89,0+5,2)-(15,6*2)))-56,3";
	arithmetic arith(Primer);
	arith.Check();
	arith.BreakLexemes();
	arith.PolishLexemes();
	ASSERT_EQ(-34, round(arith.PolishLexemesSolution()));
}



