#ifndef MOVIE_H
#define MOVIE_H
using namespace std;

class Movie {

    public:

        // constructors & destructor
        Movie();
        Movie( const Movie & movie);
        ~Movie();

        // operator overloading
        void operator = ( const Movie& m);

        // getters & setters
        long getMovieID();
        int getNumberOfSeats();

        // initalizer & member functions
        void initMovie( const long MovieID, const int audienceRadius, const int row, const int col);
        void seatingPlanPrinter();
        void bookOneSeat();
        void releaseOneSeat();
        int colConverter( const char col);
        int rowConverter( const int row);
        bool isReserved( const int row, const int col);
        void reservationMaker( const int row, const int col);
        void reservationCancel( const int row, const int col);
        int reservationCodeGenerator( const long MovieID, const int row, const char col);
        long ID_decoder( int resCode);
        int rowDecoder( int resCode);
        char colDecoder( int resCode);

    private:
        
        long movieID;
        int audienceRadius;
        int defaultRow;
        int defaultCol;

        int numOfSeats;
        int rowWithRadius;
        int colWithRadius;

        bool** seatingPlan;

        
        
};
#endif