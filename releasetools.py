# Copyright (C) 2009 The Android Open Source Project
# Copyright (C) 2018 The MoKee Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import re

def FullOTA_Assertions(info):
  AddModemAssertion(info)
  AddTreblize(info)
  return

def FullOTA_InstallEnd(info):
  AddDeunifyScript(info)
  return

def IncrementalOTA_Assertions(info):
  AddModemAssertion(info)
  AddTreblize(info)
  return

def IncrementalOTA_InstallEnd(info):
  AddDeunifyScript(info)
  return

def AddModemAssertion(info):
  android_info = info.input_zip.read("OTA/android-info.txt")
  m = re.search(r'require\s+version-modem\s*=\s*(.+)', android_info)
  if m:
    version = m.group(1).rstrip()
    if len(version) and '*' not in version:
      cmd = 'assert(osborn.verify_modem("' + version + '") == "1");'
      info.script.AppendExtra(cmd)
  return

def AddDeunifyScript(info):
  info.script.Mount("/system")
  info.script.AppendExtra('run_program("/tmp/install/bin/deunify.sh");')
  info.script.Unmount("/system")

def AddTreblize(info):
  info.script.AppendExtra('ui_print("Checking Project Treble...");');
  info.script.AppendExtra('package_extract_dir("install", "/tmp/install");');
  info.script.AppendExtra('set_metadata_recursive("/tmp/install", "uid", 0, "gid", 0, "dmode", 0755, "fmode", 0644);');
  info.script.AppendExtra('set_metadata_recursive("/tmp/install/bin", "uid", 0, "gid", 0, "dmode", 0755, "fmode", 0755);');
  info.script.AppendExtra('ifelse(is_mounted("/system"), unmount("/system"));');
  info.script.AppendExtra('if run_program("/tmp/install/bin/treblize.sh") != 0 then');
  info.script.AppendExtra('abort("Treblize failed.");');
  info.script.AppendExtra('endif;');
