/*
 * fileExists.h
 *
 *  Created on: Jul 17, 2014
 *      Author: cmaier
 */

#ifndef FILEEXISTS_H_
#define FILEEXISTS_H_

inline bool fileExists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}



#endif /* FILEEXISTS_H_ */
