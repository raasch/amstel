// -*- c++ -*-

// +------------------------------------------------------------------------+
// | This file is part of AMSTeL - the Adaptive MultiScale Template Library |
// |                                                                        |
// | Copyright (c) 2002-2023                                                |
// | Thorsten Raasch, Manuel Werner, Jens Kappei, Dominik Lellek,           |
// | Philipp Keding, Alexander Sieber, Henning Zickermann,                  |
// | Ulrich Friedrich, Dorian Vogel, Carsten Weber, Simon Wardein           |
// +------------------------------------------------------------------------+

#ifndef _AMSTEL_VECTOR_IO_H
#define _AMSTEL_VECTOR_IO_H

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

namespace AMSTeL
{
    /*
     * generic input/output routines for VECTOR classes with a standard
     * signature like that of std::vector<T>
     * We use the size() routine for determining the dimension of the vector.
     */
  
    /*!
     * generic Matlab-style stream output of the form
     * [x_1 x_2 ... x_n]
     */
    template <class VECTOR>
    void print_vector(const VECTOR& v, std::ostream& os)
    {
        os << "[";
        if (v.size() > 0)
        {
            os << v[0];
            for (unsigned int i(1); i < v.size(); i++)
                os << " " << v[i];
        }
        os << "]";
    }
  
//   /* The following file IO routines are temporarily commented out... they have to be made independent of the VECTOR instance!

//     /*!
//      * write VECTOR v to ostream
//      */
//     template <class C>
//     void writeVectorToFile(const Vector<C>& v, std::ofstream& ofs)
//     {
//         ofs.is_open();
//         if (ofs.is_open())
//         {
//             try
//             {
//                 C temp_d;
//                 for (unsigned int i=0; i<v.size(); ++i)
//                 {
//                     temp_d = v[i];
//                     ofs.write(reinterpret_cast<char*>(&temp_d), sizeof(C));
//                 }
//             }
//             catch (...)
//             {
//                 cout << "writeVectorToFile: Error while writing" << endl;
//             }
//             ofs.close();
//         }
//         else
//         {
//             cout << "writeVectorToFile: Could not write file" << endl;
//         }
//     }
    
//     template <class C>
//     void writeVectorToFile(const Vector<C>& v, const char* filename)
//     {
//         std::ofstream ofs(filename,std::ofstream::binary);
//         ofs.is_open();
//         if (ofs.is_open())
//         {
//             try
//             {
//                 C temp_d;
//                 for (unsigned int i=0; i<v.size(); ++i)
//                 {
//                     temp_d = v[i];
//                     ofs.write(reinterpret_cast<char*>(&temp_d), sizeof(C));
//                 }
//             }
//             catch (...)
//             {
//                 cout << "writeVectorToFile: Error while writing" << endl;
//             }
//             ofs.close();
//         }
//         else
//         {
//             cout << "writeVectorToFile: Could not write file" << endl;
//         }
//     }
    
//     /*!
//      * open a file written by writeVectorToFile
//      */
//     template <class C>
//     void readVectorFromFile(Vector<C>& v, std::ifstream& ifs)
//     {
//         if (ifs.is_open())
//         {
//             ifs.seekg (0, ifs.end);
//             int length = ifs.tellg()/sizeof(C);
//             ifs.seekg (0, ifs.beg);
//             v.resize(length);
        
//             for (unsigned int i=0; i<length;++i)
//             {
//                 C temp_d;
//                 try
//                 {
//                     ifs.read(reinterpret_cast<char*>(&temp_d), sizeof(C));
//                     v[i] = temp_d;
//                 }
//                 catch (...)
//                 {
//                     cout << "readVectorFromFile: Read error" << endl;
//                 }
//             }
//             ifs.close();
//         }
//         else
//         {
//             cout << "readVectorFromFile: Could not read at all" << endl;
//         }
//     }
    
//     template <class C>
//     void readVectorFromFile(Vector<C>& v, const char* filename)
//     {
//         std::ifstream ifs(filename, std::ifstream::binary);
//         if (ifs.is_open())
//         {
//             ifs.seekg (0, ifs.end);
//             int length = ifs.tellg()/sizeof(C);
//             ifs.seekg (0, ifs.beg);
//             v.resize(length);
        
//             for (unsigned int i=0; i<length;++i)
//             {
//                 C temp_d;
//                 try
//                 {
//                     ifs.read(reinterpret_cast<char*>(&temp_d), sizeof(C));
//                     v[i] = temp_d;
//                 }
//                 catch (...)
//                 {
//                     cout << "readVectorFromFile: Read error" << endl;
//                 }
//             }
//             ifs.close();
//         }
//         else
//         {
//             cout << "readVectorFromFile: Could not read at all" << endl;
//         }
//     }
//  */
}

#endif	/* _AMSTEL_VECTOR_IO_H */
