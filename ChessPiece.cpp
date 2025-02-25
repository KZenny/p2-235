#include "ChessPiece.hpp"

/**
 * @brief Default Constructor : All values 
 * Default-initializes all private members.  
 * Booleans are default-initialized to False. 
 * Default color : "BLACK"
 * Default row & columns: -1 (ie. represents that it has not been put on the board yet)
 * Default piece_size: 0
 * Default type: "NONE"
 */
ChessPiece::ChessPiece() : color_{"BLACK"}, row_{-1}, column_{-1}, movingUp_{false}, piece_size_{0}, type_{"NONE"} {} 

/**
* @brief Parameterized constructor.
* @param : A const reference to the color of the Chess Piece (a string). Set the color "BLACK" if the provided string contains non-alphabetic characters. 
*     If the string is purely alphabetic, it is converted and stored in uppercase
* @param : The 0-indexed row position of the Chess Piece (an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
* @param : The 0-indexed column position of the Chess Piece (an integer). Default value -1 if not provided, or if the value provided is outside the board's dimensions, [0, BOARD_LENGTH)
* @param : A flag indicating whether the Chess Piece is moving up on the board, or not. Default value false if not provided.
* @post : The private members are set to the values of the corresponding parameters
* ADDITIONS:
* @param : An integer representing the size of the current chess piece. 
*          Default value 0.
* @param : A string representing the type of the current chess piece. 
*          Default value "NONE".
*/
ChessPiece::ChessPiece(const std::string& color, const int& row, const int& col, const bool& movingUp, const int& size, const std::string& type) :
    color_{"BLACK"}, row_{-1}, column_{-1}, movingUp_{movingUp}, piece_size_{size}, type_{type} {
        // Check for fully alphabetical string & override "BLACK" if valid color
        setColor(color);
        
        // Set row / col if within board dimensions
        setRow(row);
        // If the row was valid, then we see if col is too.
        if (row_ != -1) { setColumn(col); }
    }

/**
 * @brief Gets the color of the chess piece.
 * @return The string value stored in color_
 */
std::string ChessPiece::getColor() const { 
    return color_; 
}

/**
 * @brief Sets the color of the chess piece.
 * @param color A const string reference, representing the color to set the piece to. 
 *     If the string contains non-alphabetic characters, the value is not set (ie. nothing happens)
 *     If the string is alphabetic, then all characters are converted and stored in uppercase
 * @post The color_ member variable is updated to the parameter value in uppercase
 * @return True if the color was set sucessfully. False otherwise.
 */
bool ChessPiece::setColor(const std::string& color) {
    std::string uppercase = "";
    for (size_t i = 0; i < color.size() && std::isalpha(color[i]); i++) {
        uppercase += std::toupper(color[i]);
    } 

    // If all param characters are successfully converted to uppercase, we use it
    if (uppercase.size() == color.size()) { 
        color_ = std::move(uppercase); 
        return true;
    }

    return false;
}

/**
 * @brief Gets the row position of the chess piece.
 * @return The integer value stored in row_
 */
int ChessPiece::getRow() const {
    return row_;
}

/**
 * @brief Sets the row position of the chess piece 
 * @param row The new row of the piece as an integer
 *  If the supplied value is outside the board dimensions [0, BOARD_LENGTH), the ChessPiece is considered to be taken off the board, and its row AND column are set to -1 instead.
 */
void ChessPiece::setRow(const int& row) {
    if (row < 0 || row >= BOARD_LENGTH) {
        row_ = -1;
        column_ = -1;
        return ;
    }
    
    row_ = row;
}

/**
 * @brief Gets the column position of the chess piece.
 * @return The integer value stored in column_
 */
int ChessPiece::getColumn() const {
    return column_;
}

/**
 * @brief Sets the column position of the chess piece 
 * @param row A const reference to an integer representing the new column of the piece 
 *  If the supplied value is outside the board dimensions [0, BOARD_LENGTH), the ChessPiece is considered to be taken off the board, and its row AND column are set to -1 instead.
 */
void ChessPiece::setColumn(const int& column) {
    if (column < 0 || column >= BOARD_LENGTH) {
        row_ = -1;
        column_ = -1;
        return ;
    }
    
    column_ = column;
}

/**
 * @brief Gets the value of the flag for if a chess piece is moving up
 * @return The boolean value stored in movingUp_
 */
bool ChessPiece::isMovingUp() const {
    return movingUp_;
}

/**
 * @brief Sets the movingUp flag of the chess piece 
 * @param flag A const reference to an boolean representing whether the piece is now moving up or not
 */
void ChessPiece::setMovingUp(const bool& flag) {
    movingUp_ = flag;
}

/**
 * @brief Displays the chess piece's information in the following format, if it is considered on the board (ie. its row and col are not -1):
 * <COLOR> PIECE at (row, col) is moving <UP / DOWN>\n
 * 
 * Otherwise an alternative format is used:
 * <COLOR> PIECE is not on the board\n
 * @note "\n" just means endline in this case. Please use "std::endl," don't hardcode "\n".
 */
void ChessPiece::display() const {
    if (row_ == -1 || column_ == -1) {
        std::cout << color_ << " piece is not on the board" << std::endl;
        return; 
    }

    std::cout << color_ << " piece at " << "(" << row_ << ", " << column_ << ") is moving " 
        << (movingUp_ ? "UP" : "DOWN") << std::endl;
}

/**
 * @brief Getter for the piece_size_ data member
 * @return The integer value stored in piece_size_
 */
int ChessPiece::size() const {
    return piece_size_;
}

/**
 * @brief Getter for the type_ data member
 * @return The string value stored in type_
 */
std::string ChessPiece::getType() const {
    return type_;
}

/**
 * @brief Sets the size of the chess piece.
 * @param size An integer representing the new size of the chess piece.
 * @note This method does not validate pre-conditions 
 *       (e.g., checking for negative sizes).
 * @post The size_ member of the ChessPiece is overridden. No value is returned.
 */
void ChessPiece::setSize(const int& size) {
    piece_size_ = size;
}

/**
 * @brief Sets the type of the chess piece.
 * @param type A const reference to a string representing the new type of the chess piece 
 *      (e.g., "ROOK", "PAWN", "NONE").
 * @note This method does not validate pre-conditions 
 *      (e.g., checking for caps or symbols in the type string).
 * @post The type_ member of the ChessPiece is overridden. No value is returned.
 */
void ChessPiece::setType(const std::string& type) {
    type_ = type;
}