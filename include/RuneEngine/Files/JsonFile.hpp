#pragma once

namespace rn
{
	class JsonFile
	{
		std::string path;
		std::string file_name;
		static void create(const std::string &path, const std::string &fname);
		static std::string getFullPath(const std::string &path, const std::string &fname);
	public:
		Json js;
		JsonFile(const std::string &path, const std::string &fname, Json j = Json());
		static Json load(const std::string &path, const std::string &fname); // loads json to file
		static Json load(const JsonFile &jsonf); // loads json to file
		Json load();
		std::string getFileName();
		std::string getPath();

		void save() const; // loads json to file
		static void save(const JsonFile &jsonf);
		static void save(std::string path, const std::string &fname, Json j = Json()); // loads json to file
	};

	
}
