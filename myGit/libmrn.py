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
        
def repo_path(repo, *path):
      """Compute path under repo's gitdir"""
      return os.path.join(repo.gitdir, *path)

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


def cmd_add(args):
    print("File added")

def cmd_cat_file(args):
    print("file cat")

def cmd_check_ignore(args):
    print("check ignore")

def cmd_checkout(args):
    print("checkout")

def cmd_commit(args):
    print("commiting")

def cmd_hash_object(args):
        print("hash-object")

def cmd_init(args):
        print("init")

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
    parse_cmd_init              = argsubparsers.add_parser("init", help="initialize git repo")
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

    # get COMMAND case for bridges function  
    args = argument_parser.parse_args(argv)

     # Call the appropriate function
    if hasattr(args, 'func'):
        args.func(args)  # This calls the command's function
    else:
        argument_parser.print_help()


main()
