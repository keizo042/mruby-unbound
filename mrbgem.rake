MRuby::Gem:Specification.new('mruby-unbound') do |spec|
    spec.licence = 'MIT'
    spec.authors = 'keizo'
    spec.linker.libraries << "unbound"

end

