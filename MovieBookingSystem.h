#ifndef MOVIEBOOKINGSYSTEM_H
#define MOVIEBOOKINGSYSTEM_H
#include "Movie.h"
#include "MovieBookingSystem.h"


using namespace std;

class MovieBookingSystem {
public:
    const static int numOfRow = 30;
    const static int numOfColumn = 26;
    
    MovieBookingSystem();
    ~MovieBookingSystem();

    void addMovie( const long movieID, const int audienceRadius );
    void cancelMovie( const long movieID );
    void showAllMovies();
    void showMovie( const long movieID );
    int makeReservation( const long movieID, const int row, const char col );
    void cancelReservations( const int numRes, const int* resCode );
    void showReservation( const int resCode );

private:

    int numOfMovies; // size of the moviesArray
    Movie* moviesArray; // Movies will be stored
    int* reservationCodesLocal; // local reservation codes of the system. these codes are kept to compare with the customer provided codes.
    int numOfReservations; // size of reservationCodesLocal array
    
    void reservationCodeKeepFunction( int resCode);

};
#endif 