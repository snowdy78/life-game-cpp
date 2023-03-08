#pragma once

#include <fstream>
#include <Windows.h>
#include "nlohmann/json.hpp"


namespace rn
{
	class JsonFile
	{
		using Json = nlohmann::json;
		std::string path;
		std::string file_name;
		static void create(const std::string &path, const std::string &fname);
		static std::string getFullPath(const std::string &path, const std::string &fname)
		{
			if (path.size() == 0)
				return fname + ".json";
			const char &lchar = path[path.size() - 1];
			return (lchar == '/' or lchar == '\\' ? path.substr(path.size() - 1) : path) + "\\" + fname + ".json"; // excepting way when file path end's "/" or "\"
		}
	public:
		Json js;
		JsonFile(const std::string path, const std::string fname, const Json j = Json()) : path(path), file_name(fname), js(j) { load(); }
		static Json load(const std::string &path, const std::string &fname); // loads json to file
		static Json load(const JsonFile &jsonf); // loads json to file
		Json load();
		std::string getFileName() { return file_name; }
		std::string getPath() { return path; }

		void save() const; // loads json to file
		static void save(const JsonFile &jsonf);
		static void save(std::string path, const std::string &fname, const Json &j = Json()); // loads json to file
	};

	inline void JsonFile::create(const std::string &path, const std::string &fname)
	{
		/*
		* create a file.
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		using namespace std::string_literals;
		std::string com = "mkdir "s + path; // cmd command >>>mkdir <path>
		system(com.c_str()); // console file creating
		std::ofstream ofile(getFullPath(path, fname));
		if (!ofile.is_open())
		{
			std::cerr << "FileOpenErr: No such file or dirrectory\n";
			throw;
		}
	}

	inline Json JsonFile::load(const std::string &path, const std::string &fname)
	{
		/*
		* loads a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		std::ifstream infile;
		const std::string full_path = getFullPath(path, fname);
		infile.open(full_path);
		if (!infile.is_open())
		{
			create(path, fname);
			infile.open(full_path);
		}
		std::string strjs = ""; // json dumped string
		std::string line;
		while (!infile.eof())
		{
			infile >> line;
			strjs += line;
		}
		infile.close();
		return Json::parse(strjs);
	}

	inline Json JsonFile::load(const JsonFile &jsonf)
	{
		/*
		* loads a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		return load(jsonf.path, jsonf.file_name);
	}

	inline Json JsonFile::load()
	{
		/*
		* loads a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		return js = load(path, file_name);
	}

	inline void JsonFile::save(std::string path, const std::string &fname, const Json &j)
	{
		/*
		* save a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		std::ofstream outf;
		const std::string full_path = getFullPath(path, fname);
		outf.open(full_path);
		if (!outf.is_open())
		{
			create(path, fname);
			outf.open(full_path);
		}
		outf << j.dump(4, ' ');
		outf.close();
	}


	inline void JsonFile::save() const
	{
		/*
		* save a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		save(path, file_name, js);
	}

	inline void JsonFile::save(const JsonFile &jsonf)
	{
		/*
		* save a file. if file not found creates a file
		* path - file dirrectory
		* fname - file name, without a file type
		*/
		save(jsonf.path, jsonf.file_name, jsonf.js);
	}
}
