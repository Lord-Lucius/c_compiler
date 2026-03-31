#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Get the directory of this script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BUILD_DIR="$SCRIPT_DIR/build"

# Function to print colored output
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Function to show help
show_help() {
    echo ""
    echo -e "${BLUE}╔════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║        C Compiler Build Script         ║${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════╝${NC}"
    echo ""
    echo "Usage: $0 [OPTION]"
    echo ""
    echo "Options:"
    echo "  build      - Build the project (configure + compile)"
    echo "  clean      - Clean the build directory"
    echo "  rebuild    - Clean and rebuild the project"
    echo "  help       - Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 build       # Build the project"
    echo "  $0 clean       # Clean build files"
    echo "  $0 rebuild     # Clean and rebuild"
    echo ""
}

# Function to clean
do_clean() {
    print_info "Cleaning build directory..."
    
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        print_success "Build directory cleaned"
    else
        print_warning "Build directory does not exist"
    fi
}

# Function to build
do_build() {
    print_info "Building project..."
    
    # Check if build directory exists, if not create it
    if [ ! -d "$BUILD_DIR" ]; then
        print_info "Creating build directory..."
        mkdir -p "$BUILD_DIR"
    fi
    
    # Go to build directory
    cd "$BUILD_DIR" || exit 1
    
    # Run CMake
    print_info "Running CMake..."
    if ! cmake ..; then
        print_error "CMake configuration failed"
        cd "$SCRIPT_DIR" || exit 1
        return 1
    fi
    
    # Run make
    print_info "Compiling..."
    if ! make; then
        print_error "Build failed"
        cd "$SCRIPT_DIR" || exit 1
        return 1
    fi
    
    # Go back to script directory
    cd "$SCRIPT_DIR" || exit 1
    
    print_success "Build completed successfully!"
    echo ""
    echo -e "${GREEN}Executable location: ${YELLOW}./build/c_compiler${NC}"
    echo ""
}

# Function to rebuild (clean + build)
do_rebuild() {
    print_info "Rebuilding project (clean + build)..."
    echo ""
    
    do_clean
    echo ""
    do_build
}

# Function to run tests
run_tests() {
    print_info "Running tests..."
    
    if [ ! -f "$BUILD_DIR/c_compiler" ]; then
        print_error "Executable not found. Build the project first!"
        return 1
    fi
    
    if [ ! -d "$SCRIPT_DIR/writing-a-c-compiler-tests" ]; then
        print_error "Test directory not found"
        return 1
    fi
    
    cd "$SCRIPT_DIR/writing-a-c-compiler-tests" || exit 1
    ./test_compiler ../build/c_compiler --chapter 1 --stage lex
    cd "$SCRIPT_DIR" || exit 1
}

# Main logic
case "${1:-help}" in
    build)
        do_build
        ;;
    clean)
        do_clean
        ;;
    rebuild)
        do_rebuild
        ;;
    test)
        do_build && run_tests
        ;;
    help)
        show_help
        ;;
    *)
        print_error "Unknown option: $1"
        show_help
        exit 1
        ;;
esac