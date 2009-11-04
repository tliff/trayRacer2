#!/usr/bin/ruby
require 'fileutils'
include FileUtils


def movefile(src, dst)
  cmd = "cat " + src + 
    "| sed s/%type%/"+$type+"/g" +
    "| sed s/%id%/"+$id+"/g" +
    "| sed s/%uctype%/"+$uctype+"/g" +
    "| sed s/%ucid%/"+$ucid+"/g" +
    "| sed s/%auctype%/"+$auctype+"/g" +
    "| sed s/%aucid%/"+$aucid+"/g" +
    " > " + dst
  system cmd
end

$type = ARGV[0]
$id = ARGV[1]
$uctype = ARGV[0]
$ucid = ARGV[1]
$auctype = ARGV[0]
$aucid = ARGV[1]

if $type == nil or $id == nil then
  puts "Sorry, not enough arguments. Try: scripts/addPlugin.rb type id" 
  exit
end
$type = $type.downcase
$id = $id.downcase
$auctype = $type.upcase
$aucid = $id.upcase

puts "Trying to create " + $uctype + ":" + $ucid 

if not File.exists? 'src' then
  puts "You seem to be in the wrong directory"
end

cd('src/plugin') do
  if not File.exists? $type then
    mkdir($type)
  end
  cd($type) do
    if not File.exists? $id then
      mkdir($id) 
      movefile('../../../scripts/pluginskel/type_id.cpp', $id+'/'+$type+'_'+$id+'.cpp')
      movefile('../../../scripts/pluginskel/type_id.hpp', $id+'/'+$type+'_'+$id+'.hpp')
      movefile('../../../scripts/pluginskel/SConscript', $id+'/SConscript')
    end
  end
end

