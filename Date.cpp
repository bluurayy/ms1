#include "Date.h"
using namespace oop244;
#include "general.h"
#include <iomanip>
#include <iostream>
using namespace std;

	// returns a uniqe value out of date
	// this value is used to compare two dates
	int Date::value()const{
		return _year * 372 + _mon * 31 + _day;
	}
	void Date::errCode(int errorCode){
		_readErrorCode = errorCode;
	}
	// validate(), this is an optional private function to write
	// for validation logic and setting the _readErrorCode.
	// see the read() funciton description for more detail
	void Date::validate(){
		
		errCode(NO_ERROR);
		if (_year < MIN_YEAR || _year > MAX_YEAR){
			errCode(YEAR_ERROR);
			
		}
		else if (_mon < 1 || _mon > 12){
			errCode(MON_ERROR);
			
		}
		else if (_day < 1 || _day > mdays()){
			errCode(DAY_ERROR);
			
		}

		
	}



  // mday():
  // returns the day of the month.
  // _mon value must be set for this to work
  // if _mon is invalid, this function returns -1
  // leap years are considered in this logic

  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
  }

  // constructors
  
  Date::Date(){

	  _year = 0;
	  _mon = 0;
	  _day = 0;
	  _readErrorCode = NO_ERROR;

  }
  Date::Date(int year, int month, int day){

	  _year = year;
	  _mon = month;
	  _day = day;
	  _readErrorCode = NO_ERROR;

  }


  // member functions

  int Date::errCode()const{
	  return _readErrorCode;
  }
  bool Date::bad()const{
		
	  if (_readErrorCode != 0){
		  return 1;
	  }
	  return 0;
  }



  // operators
  bool Date::operator==(const Date& D)const{

	  if (this->value() == D.value()){
		  return 1;
	  }
	  return 0;
  }
  bool Date::operator!=(const Date& D)const{

	  if (this->value() != D.value()){
		  return 1;
	  }
	  return 0;
  }
  bool Date::operator<(const Date& D)const{

	  if (this->value() < D.value()){
		  return 1;
	  }
	  return 0;
  }
  bool Date::operator>(const Date& D)const{

	  if (this->value() > D.value()){
		  return 1;
	  }
	  return 0;
  }

  bool Date::operator<=(const Date& D)const{

	  if (this->value() <= D.value()){
		  return 1;
	  }
	  return 0;
  }
  
  bool Date::operator>=(const Date& D)const{

	  if (this->value() >= D.value()){
		  return 1;
	  }
	  return 0;
  }
  





  // IO funtions
  istream& Date::read(istream& istr){
	
	  
	  char ch1;
	  char ch2;

	  istr >> _year;
	  istr >> ch1;
	  istr >> _mon;
	  istr >> ch2;
	  istr >> _day;
	  istr.ignore();

	  
	  validate();
		  
	  
	  if (istr.fail()){
		  _readErrorCode = CIN_FAILED;
		  return istr;
	  }
	  
	  return istr;
  }
  ostream& Date::write(ostream& ostr)const{

	  ostr << _year << "/" << _mon << "/" << _day;

	  return ostr;
  }


  // non-member operator overloads
  namespace oop244{
  std::ostream& operator<<(std::ostream& ostr, const Date& D){

		 return D.write(ostr);
	  }
  std::istream& operator>>(std::istream& istr, Date& D){

		  return D.read(istr);

	  }
  }