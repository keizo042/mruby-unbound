MRuby::Gem:Specification.new('mruby-unbound') do |spec|
    cc.flag=''
    spec.licence = 'MIT'
    spec.authors = 'keizo'
    spec.cc.include_path << "#{build.root}/src"

end

