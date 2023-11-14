string timeConversion(string s) {
    char am_pm_indicator = s[s.length()-2];
    int length_of_Substring = 6;
    string hh = s.substr(0, 2);
    if (am_pm_indicator == 'P'){
        if (hh == "12") {
            length_of_Substring = 8;
            return s.substr(0,length_of_Substring);
        } else {
            int hh_int = stoi(hh, 0, 10);
            hh_int = hh_int + 12;
            hh = to_string(hh_int);
            hh.append(s.substr(2, length_of_Substring));
            return hh;
        }
    } else if (am_pm_indicator == 'A') {
        
        if(hh == "12") {
            hh = "00";
            hh.append(s.substr(2, length_of_Substring));
            return hh;
        } else {
            length_of_Substring = 8;
            return s.substr(0,length_of_Substring);
        }
    }  
    return "error";
}
