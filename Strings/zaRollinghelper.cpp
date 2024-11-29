vector<int> isSubStrAtIndexId(int hehes,string s, string subs)
{
  for (int id=0;id<hehes.size();id++)
    {
    bool t= false;
      if(hehes[id]==1)
      {
        t=true;
        for(int i=id;i<s.size();i++)
          {
             for(int j=0;i<subs.size();j++)
          {
            if(s[i]!=s[j])t=false;
          }
          }
      }
      ids.push_back(id);
    }
  return ids;
}
