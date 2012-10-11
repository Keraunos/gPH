#include <QtTest/QtTest>
#include "PHIOTest.h"

int main (int argc, char ** argv) {
	PHIOTest test1;
	QTest::qExec(&test1);
	return 0;
}