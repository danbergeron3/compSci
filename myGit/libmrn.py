import argparse
import sys
import collections
import configparser
import grp, pwd
import hashlib
import os
import re
import zlib
from datetime import datetime
from fnmatch import fnmatch

class GitObject(object):

      def __init__(self, data=None):
            if data != None:
                  self.deserialize(data)
            else:
                  self.init()

      def serialize(self, repo):
            """This function Must be implemented by the subclass It must read the object's contents from self.data, a byte string, and do
      whatever it takes to convert it into a meaningful representation.  What exactly that means depend on each subclass."""
            raise Exception("Unimplemented!")
      
      def deserialize(self, data):
            raise Exception("Unimplemented")
      
      def init(self):
            pass # Just do nothing. This is a reasonable default!

class GitBlob(GitObject):
      fmt=b'blob'

      def serialize(self):
            return self.blobdata
      
      def deserialize(self, data):
            self.blobdata = data



class GitRepository (object):
        """A git repository under the hood"""
        # work tree is the git repository the user interacts with
        # git directory is .git holding git meta information 
        # config is config file in .git holding repo configurations
        work_tree = None
        git_directory = None
        config = None

        # given a path will 
        def __init__(self, path, force=False):
               self.work_tree = path
               self.git_directory = os.path.join(path, ".git")
               

               if not (force or os.path.isdir(self.git_directory)):
                     raise Exception("Not a Git repository %s" % path)
               
               # read configuration file in .git/config 
               self.config = configparser.ConfigParser()
               config_file = repo_file(self, "config")
               if config_file and os.path.exists(config_file):
                     self.config.read([config_file])
               elif not force:
                     raise Exception("Configuration file missing")
               
               if not force:
                     vers = int(self.config.get("core", "repositoryformatversion"))
                     if vers != 0:
                        raise Exception("Unsupported repositoryformatversion") % vers
                     
def object_read(repo, sha):
      """Read object sha from Git repository repo. Return a 
      GitObject whose exact type depends on the object."""
      
      path = repo_file(repo, "objects, sha[0:2], sha[2:]")

      if not os.path.isfile(path):
            return None
      
      with open (path, "rb") as f:
            raw = zlib.decompress(f.read())

            # Read Object type
            x = raw.find(b' ')
            fmt = raw[0:x]

            # read and validate object size 
            y = raw.find(b'\x00', x)
            size = int(raw[x:y].decode("ascii"))
            if size != len(raw)-y-1:
                  raise Exception("Malformed object {0}: bad length".format(sha))
            
            # pick constructor 
            match fmt:
                  case b'commit' : c=GitCommit
                  case b'tree'   : c=GitTree
                  case b'tag'    : c=GitTag
                  case b'blob'   : c=GitBlob
                  case _:
                        raise Exception("Unknown type {0} for object {1}".format(fmt.decode("ascii"), sha))

        # Call constructor and return object
      return c(raw[y+1:])

def object_write(obj, repo=None):
      # serialize object data
      data = obj.serialize()
      # add header 
      result = obj.fmt + b' ' + str(len(data)).encode() + b'\x00' + data
      # Compute Hash 
      sha = hashlib.sha1(result).hexdigest()

      if repo:
            # compute path 
            path=repo_file(repo, "objects", sha[0:2], sha[2:], mkdir=True)

            if not os.path.exists(path):
                  with open(path, 'wb') as f:
                        # compress and write 
                        f.write(zlib.compress(result))
      return sha



def repo_path(repo, *path):
      """Compute path under repo's git_directory"""
      return os.path.join(repo.git_directory, *path)

def repo_file(repo, *path, mkdir=False):
      """Same as repo path but create dirname(*path) if absent. For example 
      , repo_file(r,  \"refs\", \"remotes\", \"origin\", \"HEAD\") will create
        .git/refs/remotes/origin."""
      if repo_dir(repo, *path[:-1], mkdir=mkdir):
            return repo_path(repo, *path)
      
def repo_dir(repo, *path, mkdir=False):
      """Same as repo_path, but mkdir * path if absent if mkdir."""

      path = repo_path(repo, *path)

      if os.path.exists(path):
            if (os.path.isdir(path)):
                return path
            else:
                raise Exception("Not a directory %s" % path)
      if mkdir:
            os.makedirs(path)
            return path 
      else: 
            return None 

def repo_create(path):
      """Create a new repository at path."""
      repo = GitRepository(path, True)

      # first, we make sure the path either doesn't exist or is an
      # empty di

      if os.path.exists(repo.work_tree):
            if not os.path.isdir(repo.work_tree):
                  raise Exception("%s is not a directory!" % path)
            if os.path.exists(repo.git_directory) and os.listdir(repo.git_directory):
                  raise Exception("%s is not empty!" % path)
      else:
            os.makedirs(repo.work_tree)

      assert repo_dir(repo, "branches", mkdir=True)
      assert repo_dir(repo, "objects", mkdir=True)
      assert repo_dir(repo, "refs", "tags", mkdir=True)
      assert repo_dir(repo, "refs", "heads", mkdir=True)

      # .git/description
      with open(repo_file(repo, "description"), "w") as f:
            f.write("Unnamed repository; edit this file 'description' to name the repository. \n")

      #.git/HEAD
      with open(repo_file(repo, "HEAD"), "w") as f:
            f.write("ref: refs/heads/master\n")

      with open(repo_file(repo, "config"), "w") as f:
            config = repo_default_config()
            config.write(f)
      
      return repo

def repo_default_config():
      ret = configparser.ConfigParser()

      ret.add_section("core")
      ret.set("core", "repositoryformatversion", "0")
      ret.set("core", "filemode", "false")
      ret.set("core", "bare", "false")

      return ret

def object_find(repo, name, fmt=None, follow=True):
      return name 



def cmd_add(args):
    print("File added")

def cmd_cat_file(args):
      repo = repo_find()
      cat_file(repo, args.object, fmt=args.type.encode())

def cat_file(repo, obj, fmt=None):
      obj = object_read(repo, object_find(repo, obj, fmt=fmt))
      sys.stdout.buffer.write(obj.serialize())

def cmd_check_ignore(args):
    print("check ignore")

def cmd_checkout(args):
    print("checkout")

def cmd_commit(args):
    print("commiting")

def cmd_hash_object(args):
        print("hash-object")

def cmd_init(args):
      print("Creating new repo...")
      repo_create(args.path)

def cmd_log(args):
        print("log")

def cmd_ls_files(args):
      print("ls files")

def cmd_ls_tree(args):
      print("ls tree")

def cmd_rev_parse(args):
        print("rev_ parse")

def cmd_rm(args):
        print("remove")

def cmd_show_ref(args):
        print("show ref")

def cmd_status(args):
        print("status")

def cmd_tag(args):
        print("tag")

def repo_find(path=".", required=True):
      path = os.path.realpath(path)
      if os.path.isdir(os.path.join(path, ".git")):
            return GitRepository(path)
          
      # if we haven't returned, recurse in parent, if w
      parent = os.path.realpath(os.path.join(path, ".."))

      if parent == path:
            # Bottom case 
            # os.path.join("/", "..") == "/":
            # if parent ==path, then path is root.
            if required:
                  raise Exception("No git directory")
            else:
                  return None

def main(argv=sys.argv[1:]): 
    # create parser & subparser 
    argument_parser = argparse.ArgumentParser(
                        prog="mrn",
                        description="My git replacement",
                        epilog="Add source code link here")
    
    # create command namespace
    argsubparsers               = argument_parser.add_subparsers(title="Commands", dest="command")
    argsubparsers.required      = True

    # add sub parsers 
    parse_cmd_add               = argsubparsers.add_parser("add", help="add file")
    parse_cmd_cat_file          = argsubparsers.add_parser("cat-file", help="display file")
    parse_cmd_check_ignore      = argsubparsers.add_parser("check-ignore", help="search ignore file")
    parse_cmd_checkout          = argsubparsers.add_parser("checkout", help="checkout a branch")
    parse_cmd_commit            = argsubparsers.add_parser("commit", help="commit changes to working branch")
    parse_cmd_hash_object       = argsubparsers.add_parser("hash-object", help="idk")
    parse_cmd_init              = argsubparsers.add_parser("init", help="Initialize a new, empty repository.")
    parse_cmd_log               = argsubparsers.add_parser("log", help="show log file")
    parse_cmd_ls_files          = argsubparsers.add_parser("ls-files", help="list files")
    parse_cmd_ls_tree           = argsubparsers.add_parser("ls-tree", help="show file tree structure")
    parse_cmd_rev_parse         = argsubparsers.add_parser("rev-parse", help="idk")
    parse_cmd_rm                = argsubparsers.add_parser("rm", help="removes files from version control")
    parse_cmd_show_ref          = argsubparsers.add_parser("show-ref", help="idk")
    parse_cmd_status            = argsubparsers.add_parser("status", help="show status of files in version control")
    parse_cmd_tag               = argsubparsers.add_parser("tag", help="idk")
    
    # set bridge functions
    parse_cmd_add.set_defaults(func=cmd_add)
    parse_cmd_cat_file.set_defaults(func=cmd_cat_file)
    parse_cmd_check_ignore.set_defaults(func=cmd_check_ignore)
    parse_cmd_checkout.set_defaults(func=cmd_checkout)
    parse_cmd_commit.set_defaults(func=cmd_commit)
    parse_cmd_hash_object.set_defaults(func=cmd_hash_object)
    parse_cmd_init.set_defaults(func=cmd_init)
    parse_cmd_log.set_defaults(func=cmd_log)
    parse_cmd_ls_files.set_defaults(func=cmd_ls_files)
    parse_cmd_ls_tree.set_defaults(func=cmd_ls_tree)
    parse_cmd_rev_parse.set_defaults(func=cmd_rev_parse)
    parse_cmd_rm.set_defaults(func=cmd_rm)
    parse_cmd_show_ref.set_defaults(func=cmd_show_ref)
    parse_cmd_status.set_defaults(func=cmd_status)
    parse_cmd_tag.set_defaults(func=cmd_tag)


    # init commands arguments
    parse_cmd_init.add_argument("path",
                                metavar="directory",
                                nargs="?",
                                default=".",
                                help="Where to create repo")
    
    parse_cmd_cat_file.add_argument("type",
                                    metavar="type",
                                    choices=["blob", "commit", "tag", "tree"],
                                    help="Specify the type")
    
    parse_cmd_cat_file.add_argument("object",
                                    metavar="object",
                                    help="The object to display")

    
    # get COMMAND case for bridges function  
    args = argument_parser.parse_args(argv)  
     
    # Call the appropriate function
    print(args)
    if hasattr(args, 'func'):
      args.func(args)  # This calls the command's function
    else:
      argument_parser.print_help()


