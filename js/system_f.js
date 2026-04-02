/* ========================================================
   system_f.js
   Gerencia a interface, navegação e preferências do usuário
   (Equivalente funcional do system_f.h para a Web)
   ======================================================== */

// Função para Alternar Abas
function showTab(tabId) {
    // Esconder todas as sections
    document.querySelectorAll('.tab-content').forEach(section => {
        section.classList.remove('active');
    });
    // Mostrar a selecionada
    document.getElementById(tabId).classList.add('active');
    
    // Atualizar cor dos botões do menu
    document.querySelectorAll('.tab-btn').forEach(btn => {
        btn.classList.remove('active');
    });
    
    // O Event.target ou busca direta pega o botão clicado
    if (event) event.currentTarget.classList.add('active');
}

// Função do Tema (Dark/Light)
function toggleTheme() {
    document.body.classList.toggle('light-theme');
    const isLight = document.body.classList.contains('light-theme');
    const ptText = isLight ? '🌙 Dark Mode' : '☀️ Light Mode';
    document.getElementById('theme-btn').innerText = ptText;
}

// Função do Idioma (Português/Inglês)
function toggleLang() {
    const isEn = document.body.classList.contains('lang-en');
    if (isEn) {
        document.body.classList.replace('lang-en', 'lang-pt');
        document.getElementById('lang-btn').innerText = '🇺🇸 English';
    } else {
        document.body.classList.replace('lang-pt', 'lang-en');
        document.getElementById('lang-btn').innerText = '🇧🇷 Português';
    }
}