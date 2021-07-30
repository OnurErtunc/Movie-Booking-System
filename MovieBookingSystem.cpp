#include <iostream>
#include "Movie.h"
#include "MovieBookingSystem.h"
#include <ctime>
using namespace std;

/**
 * @brief Construct a new Movie Booking System:: Movie Booking System object
 * 
 */
MovieBookingSystem::MovieBookingSystem() {

    numOfMovies = 0;
    moviesArray = NULL;

    numOfReservations = 0;
    reservationCodesLocal = NULL;
}

/**
 * @brief Destroy the Movie Booking System:: Movie Booking System object
 * 
 */
MovieBookingSystem::~MovieBookingSystem() {
    if ( moviesArray != NULL ) {
        delete [] moviesArray;
    }

    if ( reservationCodesLocal != NULL ) {
        delete [] reservationCodesLocal;
    }
}

/**
 * @brief Adds a movie to the movie booking system
 * 
 * @param MovieID 
 * @param audienceRadius 
 */
void MovieBookingSystem::addMovie( const long MovieID, const int audienceRadius ) {

    if ( audienceRadius < 0 || audienceRadius > 7 ) {
        cout << "Invalid distance between the audience!" << endl;
    }
    else {
        // The case that there is no movie on the show 
        if ( moviesArray == NULL ) {
            moviesArray = new Movie[1];
            // the size of the list is 1 for efficient memory allocation purposes
            moviesArray[numOfMovies].initMovie( MovieID, audienceRadius, numOfRow, numOfColumn);
            // we added the movie. So we must increment the number of movie on the show.
            numOfMovies++;
            time_t* time = new time_t(MovieID);
            cout << "Movie at " << ctime(time) << "has been added." << endl;
            delete time;
            time = NULL;
        }
        else {
            bool alreadyExist = false;
            for ( int i = 0; i < numOfMovies; i++ ) {
                if ( moviesArray[i].getMovieID() == MovieID ) {
                    alreadyExist = true;
                }
            }
            if ( alreadyExist) {
                time_t* time = new time_t(MovieID);
                cout << "Movie at " << ctime(time) << "already exists." << endl;
                delete time;
                time = NULL;
            }
            else {
                // A new array with size + 1 will be generated for memory allocation purposes
                Movie* temp = new Movie[numOfMovies+1];
                for ( int i = 0; i < numOfMovies; i++ ) {
                    temp[i] = moviesArray[i];
                }
                delete [] moviesArray;
                
                moviesArray = temp;
                moviesArray[numOfMovies].initMovie(MovieID, audienceRadius, numOfRow, numOfColumn);
                numOfMovies++;
                temp = NULL;
                time_t* time = new time_t(MovieID);
                cout << "Movie at " << ctime(time) << "has been added." << endl;
                delete time;
                time = NULL;
            }
        }
    }
}

/**
 * @brief cancels a movie from the movie booking system
 * 
 * @param MovieID 
 */
void MovieBookingSystem::cancelMovie( const long MovieID) {
    bool found = false;
    int pos;
    for ( int i = 0; i < numOfMovies; i++ ) {
        if ( moviesArray[i].getMovieID() == MovieID ) {
            found = true;
            pos = i;
            break;
        }
    }
    if ( !found ) {
        time_t* time = new time_t(MovieID);
        cout << "Movie at " << ctime(time) << " does not exist" << endl;
        delete time;
        time = NULL;
    }
    else {
        // A new array with size - 1 will be generated for memory allocation purposes
        Movie* temp = new Movie[numOfMovies-1];
        for ( int i = 0; i < pos; i++ ) {
            temp[i] = moviesArray[i];
        }
        for ( int i = pos+1; i < numOfMovies-1; i++) {
            temp[i-1] = moviesArray[i];
        }
        delete [] moviesArray;
        moviesArray = NULL;
        moviesArray = temp;
        numOfMovies--;
        temp = NULL;
        time_t* time = new time_t(MovieID);
        cout << "Movie at " << ctime(time) << "has been cancelled." << endl;
        delete time;
        time = NULL;
    }
}

/**
 * @brief shows all movies
 * 
 */
void MovieBookingSystem::showAllMovies() {

    // the case of no movie is on show
    if ( moviesArray == NULL ) {
        cout << "No movie on show" << endl;
    }
    else {
        cout << "Movies on the show: " << endl;
        for ( int i = 0; i < numOfMovies; i++ ) {
            time_t* time = new time_t(moviesArray[i].getMovieID());
            cout << "Movie at " << ctime(time) << " (" << moviesArray[i].getNumberOfSeats();
            cout << "available seats)" << endl;
            delete time;
            time = NULL;
        }
    }
}

/**
 * @brief shows the details of a movie (number of available seats, and its seating plan)
 * 
 * @param MovieID 
 */
void MovieBookingSystem::showMovie( const long MovieID ) {

    bool found = false;
    int pos;
    for ( int i = 0; i < numOfMovies; i++ ) {
        if ( moviesArray[i].getMovieID() == MovieID ) {
            found = true;
            pos = i;
            break;
        }
    }
    if ( !found ) {
        time_t* time = new time_t(MovieID);
        cout << "Movie at " << ctime(time) << " does not exist" << endl;
        delete time;
        time = NULL;
    }
    else {
        time_t* time = new time_t(moviesArray[pos].getMovieID());
        cout << "Movie at " << ctime(time) << " (" << moviesArray[pos].getNumberOfSeats();
        cout << "available seats)" << endl;
        moviesArray[pos].seatingPlanPrinter();
        delete time;
        time = NULL;
    }
}

/**
 * @brief makes a reservation to a movie 
 * 
 * @param movieID 
 * @param row 
 * @param col 
 * @return int 
 */
int MovieBookingSystem::makeReservation( const long movieID, const int row, const char col) {
    
    bool found = false;
    int pos;
    for ( int i = 0; i < numOfMovies; i++ ) {
        if ( moviesArray[i].getMovieID() == movieID ) {
            found = true;
            pos = i;
            break;
        }
    }

    if ( !found ) {
        time_t* time = new time_t(movieID);
        cout << "Movie at " << ctime(time) << " does not exist" << endl;
        delete time;
        time = NULL;
    }
    else {
        int convertedRow = moviesArray[pos].rowConverter(row);
        int convertedCol = moviesArray[pos].colConverter(col);
        if ( moviesArray[pos].isReserved( convertedRow, convertedCol) ) {
            cout << "Seat " << col << row << " is not available in Movie at ";
            time_t* time = new time_t(moviesArray[pos].getMovieID());
            cout << ctime(time) << endl;
            delete time;
            time = NULL;
        }
        else {
            int resCode = moviesArray[pos].reservationCodeGenerator(movieID, row, col);
            reservationCodeKeepFunction(resCode);
            moviesArray[pos].reservationMaker(convertedRow, convertedCol);
            time_t* time = new time_t(moviesArray[pos].getMovieID());
            cout << "Reservation done for " << col << row << " in Movie at ";
            cout << ctime(time) << endl;
            delete time;
            time = NULL;
            return resCode;
        }
    }
    return 0;
}

/**
 * @brief cancels reservations
 * 
 * @param numRes 
 * @param resCode 
 */
void MovieBookingSystem::cancelReservations( const int numRes, const int* resCode) {

    bool found = true;
    int pos = 0;
    while ( found ) {
        if ( reservationCodesLocal[pos] != resCode[pos]) {
            found = false;
            break;
        }
        pos++;
    }

    if ( !found ) 
        cout << "Unmatched reservation code!" << endl;
    else {
        Movie tempObj;
        for ( int i = 0; i < numOfMovies; i++) {
            
            for ( int j = 0; j < numOfReservations; j++) {
                int tempID = tempObj.ID_decoder(reservationCodesLocal[j]);
                if ( tempID == moviesArray[i].getMovieID()) {
                    int tempRow = moviesArray[i].rowDecoder(reservationCodesLocal[j]);
                    char tempCol = moviesArray[i].colDecoder(reservationCodesLocal[j]);
                    int convertedRow = moviesArray[i].rowConverter(tempRow);
                    int convertedCol = moviesArray[i].colConverter(tempCol);
                    moviesArray[i].reservationCancel(convertedRow, convertedCol);
                }
            }
            
        }
    }
    delete [] reservationCodesLocal;
    reservationCodesLocal = NULL; // assigned as null to be sure that it is not pointing to reservationCodesLocal array
}
/**
 * @brief shows the reservation with given reservation code
 * 
 * @param resCode 
 */
void MovieBookingSystem::showReservation( const int resCode) {
    long decodedID = ( ( resCode-(resCode % 10000) ) + 1610001273 );
    int decodedRow = ( (resCode-(resCode%100)) / 100 ) % 100;
    char decodedCol = char(resCode %100);
    
    bool found = false;
    int pos;
    for ( int i = 0; i < numOfMovies; i++ ) {
        if ( moviesArray[i].getMovieID() == decodedID ) {
            found = true;
            pos = i;
            break;
        }
    }
    if ( !found ) {
        time_t* time = new time_t(decodedID);
        cout << "Movie at " << ctime(time) << " does not exist" << endl;
        delete time;
        time = NULL;
    }
    else {
        int convertedRow = moviesArray[pos].rowConverter(decodedRow);
        int convertedCol = moviesArray[pos].colConverter(decodedCol);
        if ( !moviesArray[pos].isReserved(convertedRow, convertedCol) ) {
            cout << "No reservation with Code " << resCode << endl;
        }
        else {
            time_t* time = new time_t(moviesArray[pos].getMovieID());
            cout << "Reservation with Code " << resCode << ": Seat " << decodedCol << decodedRow;
            cout << " in Movie at " << ctime(time) << endl;
            delete time;
            time = NULL;
        }
    }
}

/**
 * @brief keeps reservation codes as a local data
 * 
 * @param resCode 
 */
void MovieBookingSystem::reservationCodeKeepFunction( int resCode) {

    if ( reservationCodesLocal == NULL ) {
        reservationCodesLocal = new int[1];
        reservationCodesLocal[numOfReservations] = resCode;
        numOfReservations++;
    }
    else {
        int* tempReservations = new int[numOfReservations+1];
        for ( int i = 0; i < numOfReservations; i++ ) {
            tempReservations[i] = reservationCodesLocal[i];
        }
        delete [] reservationCodesLocal;
        reservationCodesLocal = NULL;
        reservationCodesLocal = tempReservations;
        reservationCodesLocal[numOfReservations] = resCode;
        tempReservations = NULL;
    }
}