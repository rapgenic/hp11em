/*
    Copyright (C) 2015 Giulio Girardi.

    This file is part of HP11em.

    HP11em is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HP11em is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HP11em.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COREAUTOSAVE_H
#define COREAUTOSAVE_H

#include "config.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <pwd.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

template <class T> class CoreAutosave {
public:
  CoreAutosave() {
    char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
      homedir = getpwuid(getuid())->pw_dir;
    }

    this->homedir = std::string(homedir);

    if (stat((this->homedir + CONFIG_DIR).data(), new struct stat) == -1) {
      mkdir((this->homedir + CONFIG_DIR).data(), 0700);
    }
  };

  virtual ~CoreAutosave(){};

protected:
  int _load() {
    std::vector<T> data;
    std::ifstream file(homedir + CONFIG_DIR + getClassName());
    T val;

    if (file.is_open()) {
      for (int i = 0; file >> val; i++) {
        data.push_back(val);
      }
    }

    if (data.size() != 0) {
      load(data);
    }

    return 1;
  };

  int _save() {
    std::ofstream file(homedir + CONFIG_DIR + getClassName(), std::ios::trunc);
    std::vector<T> data = save();

    if (file.is_open()) {
      for (unsigned int i = 0; i < data.size(); i++) {
        file << std::scientific << std::setprecision(10) << data[i] << " ";
      }
    }

    file.close();

    return 1;
  };

private:
  virtual std::string getClassName() = 0;
  virtual void load(std::vector<T> data) = 0;
  virtual std::vector<T> save() = 0;

  std::string homedir = "";
};

#endif /* COREAUTOSAVE_H */
