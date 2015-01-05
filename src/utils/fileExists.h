/**
 * @file   fileExists.h
 * @author Christopher Maier
 * @date   January 2015
 *
 * Encapsulates checking whether or not a specific file exists.
 */

#ifndef FILEEXISTS_H_
#define FILEEXISTS_H_

/**
 * Checks whether or not a file exists.
 * @param name The name of the file.
 * @return True if the file exists, false otherwise.
 */
inline bool fileExists(const std::string& name)
{
  if (FILE *file = fopen(name.c_str(), "r"))
  {
    fclose(file);
    return true;
  }
  else
  {
    return false;
  }
}

#endif /* FILEEXISTS_H_ */
