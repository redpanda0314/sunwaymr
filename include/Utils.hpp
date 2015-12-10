#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <vector>
using namespace std;

int splitString(const std::string& str, std::vector<std::string>& ret, const std::string& sep)
{
	if (str.empty())
	    {
	        return 0;
	    }

	    string tmp;
	    string::size_type pos_begin = str.find_first_not_of(sep);
	    string::size_type comma_pos = 0;

	    while (pos_begin != string::npos)
	    {
	        comma_pos = str.find(sep, pos_begin);
	        if (comma_pos != string::npos)
	        {
	            tmp = str.substr(pos_begin, comma_pos - pos_begin);
	            pos_begin = comma_pos + sep.length();
	        }
	        else
	        {
	            tmp = str.substr(pos_begin);
	            pos_begin = comma_pos;
	        }

	        if (!tmp.empty())
	        {
	            ret.push_back(tmp);
	            tmp.clear();
	        }
	    }
	    return 0;
}


std::vector<std::string> &splitString(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> splitString(const std::string &s, char delim) {
    std::vector<std::string> elems;
    splitString(s, delim, elems);
    return elems;
}

string fileNameFromPath(string const& pathname )
{
	return pathname.substr(pathname.find_last_of("/\\") + 1);
}

int vectorFind(vector<string>& v, string value){
	int index=-1;
	int vs=v.size();
	for( int i=0;i<vs;i++){
		if(v[i]==value){
			index=i;
			break;
		}
	}
	return index;
}


vector<int> vectorFindAll(vector<string>& v, string value){
	vector<int>  indexVector;
	//int index=-1;
	int vs=v.size();
	for( int i=0;i<vs;i++){
		if(v[i]==value){
			//ndex=i;
            indexVector.push_back(i);
		}
	}
	if(indexVector.size()==0){
		indexVector.push_back(-1);
	}

	return indexVector;
}

int vectorNonZero(vector<int>& v){
	int index=-1;
	int vs=v.size();
	for( int i=0;i<vs;i++){
		if(v[i]!=0){
			index=i;
			break;
		}
	}
	return index;
}

int vectorIntMax(vector<int>& v){
	int value=*max_element(v.begin(),v.end());
	int index=-1;
	int vs=v.size();
	for( int i=0;i<vs;i++){
		if(v[i]==value){
			index=i;
			break;
		}
	}
	return index;
}

int vectorSum(vector<int>& v){
	int sum=0;
	int vs=v.size();
	for( int i=0;i<vs;i++){
		sum+=v[i];
	}
	return sum;
}

vector<int> vectorTimes(vector<int>& v,float m){
	vector<int> uv;
	int vs=v.size();
	for( int i=0;i<vs;i++){
		uv.push_back(ceil(v[i]*m));
	}
	return uv;
}


long getCurrentTime()
{
   struct timeval tv;
   gettimeofday(&tv,NULL);
   return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int randomValue(int start, int end) {
	int ret = start;
	srand(getCurrentTime());
	if (start != end) {
		if (start < end) {
			ret = start + rand() % (end - start);
		} else {
			ret = end + rand() % (start - end);
		}
	}
	return ret;
}

string getLocalHost() {
	string ret = "";

    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);

            string temp = string(addressBuffer);
            string lo = "127.0.0.1";
            if (!temp.compare(0, lo.size(), lo)) ret = temp;

        } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);

    return ret;
}

void mkdirRecursive(const char *dir) {
        char tmp[256];
        char *p = NULL;
        size_t len;

        snprintf(tmp, sizeof(tmp),"%s",dir);
        len = strlen(tmp);
        if(tmp[len - 1] == '/')
                tmp[len - 1] = 0;
        for(p = tmp + 1; *p; p++)
                if(*p == '/') {
                        *p = 0;
                        mkdir(tmp, S_IRWXU);
                        *p = '/';
                }
        mkdir(tmp, S_IRWXU);
}


bool writeFile(string dir, string fileName, string content) {
	mkdirRecursive(dir.c_str());
	stringstream path;
	path << dir << fileName;
	ofstream file;
	file.open(path.str().c_str(), ios::out | ios::trunc);
	if (file.is_open()) {
		file << content;
		file.close();
		return true;
	} else {
		return false;
	}
}

bool readFile(string path,  string &content) {
	std::ifstream file(path.c_str(), std::ifstream::in);
	if (file.is_open()) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		content = buffer.str();
		file.close();
		return true;
	} else {
		return false;
	}
}


#endif /* UTILS_HPP_ */