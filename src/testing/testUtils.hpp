#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif

#define PRINT_TEST_START std::cout<<"\t"<<__PRETTY_FUNCTION__ << ":"
#define PRINT_NOT_YET_IMPLEMENTED PRINT_TEST_START "[TEST NOT YET IMPLEMENTED]:";numUnimplemented++; return false
#define PRINT_REQ_MANUAL_CHECK_NO_RETURN PRINT_TEST_START "[REQUIRES MANUAL CHECK]";requireManualCheck++
#define PRINT_REQ_MANUAL_CHECK PRINT_REQ_MANUAL_CHECK_NO_RETURN;return true;

int numSuccess=0;
int requireManualCheck=0;
int numFail=0;
int numUnimplemented=0;
int numFilesTested=0;
void printIfOK(bool ok)
{
	if(ok)
	{
		std::cout<<"[OK]\n";
		numSuccess++;
	}else
	{
		std::cout<<"[FAIL]\n";
		numFail++;
	}
}
#endif
