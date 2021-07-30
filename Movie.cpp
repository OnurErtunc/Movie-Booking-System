#include "Movie.h"
#include <iostream>
using namespace std;

/**
 * @brief Movie Object - performs the functionalities of a movie
 * @author Onur Ertunc
 * @version 0.1
 * 
 */

// Constructors and destructor

/**
 * @brief Construct a new Movie:: Movie object
 * 
 */
Movie::Movie() {
    this->movieID = 0;
    this->audienceRadius = 0;
    this->seatingPlan = NULL;

}

/**
 * @brief Construct a new Movie:: Movie object --- copy constructor
 * @param movie 
 */
Movie::Movie( const Movie & movie) {
    this->movieID = movie.movieID;
    this->audienceRadius = movie.audienceRadius;

    this->rowWithRadius = movie.rowWithRadius;
    this->colWithRadius = movie.colWithRadius;
    this->numOfSeats = movie.numOfSeats;

    this->seatingPlan = movie.seatingPlan;

    numOfSeats = rowWithRadius * colWithRadius;

    seatingPlan = new bool*[rowWithRadius];

    for ( int i = 0; i < rowWithRadius; i++ ) {
        seatingPlan[i] = new bool[colWithRadius];
    }
    for ( int i = 0; i < rowWithRadius; i++ ) {
        for ( int j = 0; j < colWithRadius; j++ ) {
            seatingPlan[i][j] = false;
        } 
    }
}

/**
 * @brief Destroy the Movie:: Movie object
 * 
 */
Movie::~Movie() {
    if ( seatingPlan != NULL ) {
        for ( int i = 0; i < rowWithRadius; i++) {
            delete [] seatingPlan[i];
        }
        delete [] seatingPlan;
    }
    else {
        delete [] seatingPlan;
    }
}

// operator overloading
/**
 * @brief assignment operator overloading for dynamic memory allocation purposes
 * in the MovieBookingSystem class, while adding or cancelling a movie into the system,
 * we are creating a new array with size+1 or size-1. doing this, we have to copy the previous
 * movies to new array. this copy operation is done by the overloaded assignment operator.
 * 
 * @param m 
 */
void Movie::operator=( const Movie& m) {
    this->movieID = m.movieID;
    this->audienceRadius = m.audienceRadius;
    this->defaultRow = m.defaultRow;
    this->defaultCol = m.defaultCol;

    this->rowWithRadius = m.rowWithRadius;
    this->colWithRadius = m.colWithRadius;
    this->numOfSeats = m.numOfSeats;

    this->seatingPlan = m.seatingPlan;

    numOfSeats = rowWithRadius * colWithRadius;

    seatingPlan = new bool*[rowWithRadius];

    for ( int i = 0; i < rowWithRadius; i++ ) {
        seatingPlan[i] = new bool[colWithRadius];
    }
    for ( int i = 0; i < rowWithRadius; i++ ) {
        for ( int j = 0; j < colWithRadius; j++ ) {
            seatingPlan[i][j] = false;
        } 
    }
}
// Member functions

/**
 * @brief initializes a movie after it is constructed
 * 
 * @param movieID 
 * @param audienceRadius 
 * @param row 
 * @param col 
 */
void Movie::initMovie( const long movieID, const int audienceRadius, const int row, const int col) {
    this->movieID = movieID;
    this->audienceRadius = audienceRadius;
    this->defaultRow = row;
    this->defaultCol = col;

    if ( (defaultRow % (audienceRadius+1) ) == 0 ) {
        this->rowWithRadius = defaultRow / (audienceRadius+1);
    }
    else {
        this->rowWithRadius = ( ( defaultRow - ( defaultRow % (audienceRadius+1) ) ) / (audienceRadius+1) ) + 1;
    }
    if ( (defaultCol % (audienceRadius+1) ) == 0 ) {
        this->colWithRadius = defaultCol / (audienceRadius+1);
    }
    else {
        this->colWithRadius = ( ( defaultCol - ( defaultCol % (audienceRadius+1) ) ) / (audienceRadius+1) ) + 1;
    }
    numOfSeats = rowWithRadius * colWithRadius;

    seatingPlan = new bool*[rowWithRadius];

    for ( int i = 0; i < rowWithRadius; i++ ) {
        seatingPlan[i] = new bool[colWithRadius];
    }
    for ( int i = 0; i < rowWithRadius; i++ ) {
        for ( int j = 0; j < colWithRadius; j++ ) {
            seatingPlan[i][j] = false;
        } 
    }
}

void Movie::seatingPlanPrinter() {
    cout << "  ";
    int increment = audienceRadius + 1;
    int m = 1;
    cout << " ";
    for ( char ch = 'A'; ch <= 'Z'; ch = ch + increment ) {
        cout << " " << ch;
    }
    cout << endl;
    for ( int i = 0; i < rowWithRadius; i++ ) {
        cout << m;
        if ( m < 10 ) {
            cout << "   ";
        }
        else {
            cout << "  ";
        }
        for ( int j = 0; j < colWithRadius; j++) {
            if ( seatingPlan[i][j]) {
                cout << "o ";
            }
            else {
                cout << "x ";
            }
        }
        cout << endl;
        m = m + increment;
    }
}

/**
 * @brief converts char column to corresponding number to use in array 
 * 
 * @param col 
 * @return int 
 */
int Movie::colConverter( const char col) {
    char ch;
    bool found = false;
    for ( ch = 'A'; ch <= 'Z' && !found; ch++ ) {
        if ( ch == col ) {
            found = true;
        }
    }
    ch = ch - 'A';
    return ch / (audienceRadius + 1); 
}

/**
 * @brief converts row value to corresponding number to use in array 
 * @param row 
 * @return int 
 */
int Movie::rowConverter( const int row) {
    return ( row - 1 ) / (audienceRadius + 1); 
}

/**
 * @brief shows the selected seat is reserved before (with array index values)
 * 
 * @param row 
 * @param col 
 * @return true 
 * @return false 
 */
bool Movie::isReserved( const int row, const int col) {
    if ( seatingPlan[row][col] ) {
        return true;
    }
    return false;
}

/**
 * @brief makes a reservation by using the seating plan
 * 
 * @param row 
 * @param col 
 */
void Movie::reservationMaker( const int row, const int col) {
    seatingPlan[row][col] = true;
    bookOneSeat();
}

/**
 * @brief cancels a reservation by using the seating plan
 * 
 * @param row 
 * @param col 
 */
void Movie::reservationCancel( const int row, const int col) {
    seatingPlan[row][col] = false;
    releaseOneSeat();
}

/**
 * @brief generates reservation code based on movieID and seat position
 * 
 * @param MovieID 
 * @param row 
 * @param col 
 * @return int 
 */
int Movie::reservationCodeGenerator( const long MovieID, const int row, const char col) {
    long temp = movieID;
    temp = movieID - ( movieID % 10000);
    temp = temp % 10000000;
    return temp + row*100 + col;
}

/**
 * @brief decodes movie id from passed reservation code
 * 
 * @param resCode 
 * @return long 
 */
long Movie::ID_decoder( int resCode) {
    return ( ( resCode-(resCode % 10000) ) + 1610001273 );
}

/**
 * @brief decodes row number from passed reservation code
 * 
 * @param resCode 
 * @return int 
 */
int Movie::rowDecoder( int resCode) {
    return ( (resCode-(resCode%100)) / 100 ) % 100;
}

/**
 * @brief decodes column char from passed reservation code
 * 
 * @param resCode 
 * @return char 
 */
char Movie::colDecoder( int resCode) {
    return char(resCode%100);
}

/**
 * @brief books one seat (as a number)
 * 
 */
void Movie::bookOneSeat() {
    this->numOfSeats = numOfSeats - 1;
}

/**
 * @brief releases one seat (as a number)
 * 
 */
void Movie::releaseOneSeat() {
    this->numOfSeats = numOfSeats + 1;
}

// Getters & setters

/**
 * @brief getter of the ID of movie
 * 
 * @return long 
 */
long Movie::getMovieID() {
    return movieID;
} 

/**
 * @brief getter of the number of seats
 * 
 * @return int 
 */
int Movie::getNumberOfSeats() {
    return numOfSeats;
}
