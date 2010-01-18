COMPILER = 'g++'
SOURCE_DIRECTORIES = ['src', 'src/math']
INCLUDE_DIRS = ['/opt/local/include', '/opt/local/lib/ruby/1.8/i686-darwin10']
LIBS = ["boost_serialization-mt", 
        "boost_unit_test_framework-mt", 
        "boost_regex-mt", 
        "boost_filesystem-mt", 
        "boost_system-mt",
        "ruby",
        "dl"].map{|l| "-l#{l}"}.join(" ")
LIB_DIRS = ["/opt/local/lib"].map{|l| "-L#{l}"}.join(" ")
BUILD_DIR = "build"
CFLAGS=["-fPIC", "-O2"].join(' ')


task :default => [:compile, :swig, :link] 

#########################################

INCLUDES = (SOURCE_DIRECTORIES + INCLUDE_DIRS).map{|d| "-I#{d}"}.join(' ')

class SourceFile
  attr_accessor :path
  attr_accessor :filename
  attr_accessor :extension
  attr_accessor :filename_no_ext
  attr_accessor :filename_built

  def initialize(f)
    parts = File::split(f)
    @path = parts[0]
    @filename = parts[1]
    @extension = File::extname(@filename)
    @filename_no_ext = @filename[0,@filename.length  - @extension.length]
    @filename_built = "#{@filename_no_ext}.o"
  end
  
  def out_of_date?
    (File::exists?("#{BUILD_DIR}/obj/#{@filename_built}") && File::stat("#{@path}/#{@filename}").mtime < File::stat("#{BUILD_DIR}/obj/#{@filename_built}").mtime)
  end
end


task :compile => [:check_builddir] do 
  puts "Compiling..."
  SOURCE_DIRECTORIES.map{|d| Dir.glob("#{d}/*.cpp")}.flatten.map{|s| SourceFile.new s}.each{ |s|
    print "#{s.filename}: "
    if s.out_of_date?
      puts "not changed"
    else
      cmd = "#{COMPILER} #{CFLAGS} #{INCLUDES} -c #{s.path}/#{s.filename} -o #{BUILD_DIR}/obj/#{s.filename_built}"
      puts cmd
      system cmd
    end
  }
  
end

task :check_builddir do
  Dir.mkdir("#{BUILD_DIR}") unless File.exists?("#{BUILD_DIR}")
  Dir.mkdir("#{BUILD_DIR}/obj") unless File.exists?("#{BUILD_DIR}/obj")
end

task :link do
  puts "Linking..."
  cmd = "g++ -L/opt/local/lib -shared -o trayracer.bundle #{BUILD_DIR}/trayRacer2_swig.o #{BUILD_DIR}/obj/* -lboost_serialization-mt -lboost_unit_test_framework-mt -lboost_regex-mt -lboost_filesystem-mt -lboost_system-mt -lruby -ldl"
  puts cmd
  system cmd
end


task :swig  => [:swig_import, :swig_compile]

task :swig_import do
  cmd = "swig -c++ -ruby -o #{BUILD_DIR}/trayRacer2_swig.cpp src/trayRacer2.i"
  puts cmd
  system cmd
  
end

task :swig_compile do
  cmd = "#{COMPILER} #{CFLAGS} #{INCLUDES} -c #{BUILD_DIR}/trayRacer2_swig.cpp -o #{BUILD_DIR}/trayRacer2_swig.o"
  "g++ -c #{BUILD_DIR}/trayRacer2_swig.cpp -o #{BUILD_DIR}/trayRacer2_swig.o -I/usr/local/lib/ruby/1.6/i686-linux "
  puts cmd
  system cmd
end

# task :swig_link do
#   cmd = "#{COMPILER} #{LIB_DIRS} -shared -o build/trayracer.so #{BUILD_DIR}/obj/*.o #{LIBS} swig.o"
#   puts cmd
#   system cmd
# end


task :clean do
  system("rm -r #{BUILD_DIR}/*")
end